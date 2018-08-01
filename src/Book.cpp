///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include "libs/blzip/BLUnZip.h"
#include "libs/tinyxml2/tinyxml2.h"

#include "Book.hpp"

Book::Book(const std::string& book)
:m_zip("sdmc:/books/" + book)
{
}

Book::~Book()
{
	m_zip.Close();
}

void Book::parse()
{
	// Parse Container. This is the same for all 3 of the supported formats.
	// -------------------------------

	// Get the container xml
	std::string containerData = m_zip.ExtractToString("META-INF/container.xml");

	// Parse that xml with tinyxml2
	tinyxml2::XMLDocument containerDoc;
    containerDoc.Parse(containerData.c_str());

    // Then navigate to method containing the OPF.
    tinyxml2::XMLElement* container = containerDoc.FirstChildElement("container");
    tinyxml2::XMLElement* rootfiles = container->FirstChildElement("rootfiles");
    tinyxml2::XMLElement* rootfile = rootfiles->FirstChildElement("rootfile");

    m_opf = rootfile->Attribute("full-path");

    // -------------------------------


    // Parse OPF
    // -------------------------------
 	std::string opfData = m_zip.ExtractToString(m_opf);
 	
 	tinyxml2::XMLDocument opfDoc;
 	opfDoc.Parse(opfData.c_str());

 	// This is the same for all 3 supported formats.
 	// Package (root document)
 	tinyxml2::XMLElement* package = opfDoc.FirstChildElement("package");
    tinyxml2::XMLElement* metadata = package->FirstChildElement("metadata");
   
    // Manifest
    tinyxml2::XMLElement* manifest = package->FirstChildElement("manifest");
    tinyxml2::XMLElement* item = manifest->FirstChildElement("item");

    // Spine
    tinyxml2::XMLElement* spine = package->FirstChildElement("spine");
    tinyxml2::XMLElement* itemref = spine->FirstChildElement("itemref");

    // Version, title and author.
    m_version = package->FloatAttribute("version");
    m_title = metadata->FirstChildElement("dc:title")->GetText();
    m_author = metadata->FirstChildElement("dc:creator")->GetText();

    // -------------------------------

    // Parse Manifest
    // -------------------------------

    for(tinyxml2::XMLElement* rfe = item; rfe != nullptr; rfe = rfe->NextSiblingElement("item"))
    {
    	// Item element id, then constructs an Item element containing type and href.
    	// See Manifest.hpp
    	Item elItem;
    	elItem.m_type = rfe->Attribute("media-type");
    	elItem.m_href = rfe->Attribute("href");

    	m_manifest.emplace(rfe->Attribute("id"), elItem);
    }

    // -------------------------------

    // Parse Spine
    // -------------------------------

    for (tinyxml2::XMLElement* it = itemref; it != nullptr; it = it->NextSiblingElement("itemref"))
    {
    	// This pushes the spine back in page order.
        m_spine.push_back(it->Attribute("idref"));
    }

    // -------------------------------
}