///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#include <locale>

#include "Book.hpp"
#include "Locator.hpp"
#include "Textures.hpp"

#include "SwitchContainer.hpp"

// https://old.reddit.com/r/NintendoSwitch/comments/5oiqn8/nintendo_switchs_ppi_pixels_per_inch_is_actually/
#define SWITCH_PPI 237.0

SwitchContainer::~SwitchContainer()
{
	// Make sure fonts are cleaned up.
	for (Font* font : m_fonts)
	{
		if (font != nullptr)
		{
			font->destroy();
		}
	}

	m_fonts.clear();
}

void SwitchContainer::setWindow(Window* window)
{
	m_window = window;
}

litehtml::uint_ptr SwitchContainer::create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm)
{
	// All fonts have the same base.
	std::string fontFile = "romfs:/fonts/SourceSansPro-Light.ttf";

	// Now determine style.
	auto style = TTF_STYLE_NORMAL;

	// A weight of 700 or greater is bold.
	if (weight >= 700)
	{
		style = style | TTF_STYLE_BOLD;
	}

	// Have to check if font is italic or not.
	if (italic == litehtml::font_style::fontStyleItalic)
	{
		style = style | TTF_STYLE_ITALIC;
	}

	// Now check for decorations.
	if ( ( decoration & litehtml::font_decoration_underline ) != 0)
	{
		style = style | TTF_STYLE_UNDERLINE;
	}

	if ( ( decoration & litehtml::font_decoration_linethrough ) != 0)
	{
		style = style | TTF_STYLE_STRIKETHROUGH;
	}

	Font* font = new Font;
	font->create(fontFile.c_str(), size, style);

	// Now do font metrics.
	int w = 0, h = 0;
	TTF_SizeText(font->getFont(), "x", &w, &h);

	fm->height = TTF_FontHeight(font->getFont());
	fm->ascent = TTF_FontAscent(font->getFont());
	fm->descent = TTF_FontDescent(font->getFont());
	fm->x_height = h;
	fm->draw_spaces = true;

	// Keep track of font, to ensure it is cleaned up.
	m_fonts.push_back(font);

	return static_cast<litehtml::uint_ptr>(font);
}

void SwitchContainer::delete_font(litehtml::uint_ptr hFont)
{
	// Get font.
	Font* font = static_cast<Font*>(hFont);
	
	if (font != nullptr)
	{
		// Destroy what the font uses.
		font->destroy();
		
		// Then delete the font.
		delete font;
		font = nullptr;
	}
}

int SwitchContainer::text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont)
{
	// Get font.
	Font* font = static_cast<Font*>(hFont);
	
	int w = 0;	
	if (font != nullptr)
	{
		int h = 0;
		TTF_SizeText(font->getFont(), text, &w, &h);
	}

	return w;
}

void SwitchContainer::draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos)
{
	// Get font.
	Font* font = static_cast<Font*>(hFont);

	// Convert colour to sdl2.
	SDL_Colour col;
	//col.r = color.red;
	//col.g = color.green;
	//col.b = color.blue;
	//col.a = color.alpha;

	// for now, assume text is black.
	col.r = 0;
	col.g = 0;
	col.b = 0;
	col.a = 255;	

	// Draw text.
	// todo: adjust
	font->renderText(m_window, text, col, pos.left(), pos.top());
}

int SwitchContainer::pt_to_px(int pt)
{
	return (pt * SWITCH_PPI / 72.0);
}

int SwitchContainer::get_default_font_size() const
{
	return 18;
}

const litehtml::tchar_t* SwitchContainer::get_default_font_name() const
{
	// Don't need a default font.
	return "";
}

void SwitchContainer::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker)
{
	/*
	 	todo: support this, see:
	
		libs/litehtml/types.h
		libs/litehtml/html.h
		and sdl2_gfx for drawing primitives
	*/
}

void SwitchContainer::load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready)
{ 
	/*
		our images are loaded and cached elsewhere, so this method is not needed.
	*/
}

void SwitchContainer::get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz)
{ 
	// src = src from <img> tag, which is a substring of the href in the manifest, which is identified by the "image/fileextension" in media-type
	// Pretty self-explainatory function. Finds the texture from a partial or even full key, and then querys it.
	Texture* texture = Locator::s_textures.findFromPartial(src);

	if (texture != nullptr)
	{
		sz.width = texture->getWidth();
		sz.height = texture->getHeight();
	}
}

void SwitchContainer::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg)
{ 
	if (!bg.image.empty())
	{
		// draw image
		// bg.image = src from <img> element, i.e. image key.
		
		if (bg.is_root)
		{
			// Retrieve positions and values of what to draw, except for root position is always 0, 0.
			// Using the src rectangle here may need adjustment.
			Texture* texture = Locator::s_textures.findFromPartial(bg.image);
			SDL_Rect src = { bg.clip_box.x, bg.clip_box.y, bg.clip_box.width, bg.clip_box.height };
			SDL_Rect dest = { 0, 0, bg.image_size.width, bg.image_size.height };

			// Draw background.
			SDL_SetRenderDrawColor(m_window->getRenderer(), bg.color.red, bg.color.green, bg.color.blue, bg.color.alpha);
			texture->draw(*m_window, &src, &dest);
		}
		else
		{
			// Retrieve positions and values of what to draw.
			// Using the src rectangle here may need adjustment.
			Texture* texture = Locator::s_textures.findFromPartial(bg.image);
			SDL_Rect src = { bg.clip_box.x, bg.clip_box.y, bg.clip_box.width, bg.clip_box.height };
			SDL_Rect dest = { bg.position_x, bg.position_y, bg.image_size.width, bg.image_size.height };

			// Draw background.
			SDL_SetRenderDrawColor(m_window->getRenderer(), bg.color.red, bg.color.green, bg.color.blue, bg.color.alpha);
			texture->draw(*m_window, &src, &dest);
		}
	}
	else
	{
		// draw background

		if (bg.is_root)
		{
			// If root i.e. <body>, just set the background render colour. Easy.
			SDL_SetRenderDrawColor(m_window->getRenderer(), bg.color.red, bg.color.green, bg.color.blue, bg.color.alpha);
		}
		else
		{
			// Otherwise get the dimensions of the image to fill, and render a rectangle with that colour.
			SDL_Rect rect = { bg.clip_box.x, bg.clip_box.y, bg.clip_box.width, bg.clip_box.height };
      		
      		SDL_SetRenderDrawColor(m_window->getRenderer(), bg.color.red, bg.color.green, bg.color.blue, bg.color.alpha);
			SDL_RenderFillRect(m_window->getRenderer(), &rect);
		}
	}
}

void SwitchContainer::draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root)
{ 
	// todo: support this
}

void SwitchContainer::set_caption(const litehtml::tchar_t* caption)
{ 
	// don't use this, so can just set to empty.
	caption = "";
}

void SwitchContainer::set_base_url(const litehtml::tchar_t* base_url)
{ 
	// don't use this, so can just set to empty.
	base_url = "";
}

void SwitchContainer::link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr& el)
{ 
	// dont need this
}

void SwitchContainer::on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el)
{
	// dont need this	
}

void SwitchContainer::set_cursor(const litehtml::tchar_t* cursor)
{ 
	// dont need this
}

void SwitchContainer::transform_text(litehtml::tstring& text, litehtml::text_transform tt)
{ 
	// Temporary code.
	// Because this is complicated process and the solution below ignores unicode.
	// Use http://site.icu-project.org/ maybe?

	switch (tt)
	{
		case litehtml::text_transform::text_transform_capitalize:
		{
			std::toupper(text[0], std::locale());
		}
		break;

		case litehtml::text_transform::text_transform_uppercase:
		{
			for (long unsigned int i = 0; i < text.length(); ++i)
			{
				std::toupper(text[i], std::locale());
			}
		}
		break;

		case litehtml::text_transform::text_transform_lowercase:
		{
			for (long unsigned int i = 0; i < text.length(); ++i)
			{
				std::tolower(text[i], std::locale());
			}
		}
		break;
	}
}

void SwitchContainer::import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl)
{
	for (auto& pair : Locator::s_book->getManifest())
	{
		if (pair.second.m_type.find("css") != std::string::npos)
		{
			auto posA = pair.second.m_href.find_last_of("/");
			if (posA != std::string::npos)
			{
				posA += 1;				
			}
			else
			{
				posA = 0;
			}

			auto posB = pair.second.m_href.find_last_of(".");
			if (posB != std::string::npos)
			{
				posB -= posA;
			}

			std::string partialKey = pair.second.m_href.substr(posA, posB);
			// convert to std::string
			std::string strURL = url;

			if (strURL.find(partialKey) != std::string::npos)
			{
				text = Locator::s_book->getZip().ExtractToString(pair.second.m_href);
			}
		}
	}
}

void SwitchContainer::set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y)
{ 
	// not sure, dont think this is used.
}

void SwitchContainer::del_clip()
{ 
	// not sure, dont think this is used.	
}

void SwitchContainer::get_client_rect(litehtml::position& client) const
{
	// Fill with switch dimensions.
	client.x = 0;
	client.y = 0;
	client.width = 1280;
	client.height = 720;
}

std::shared_ptr<litehtml::element> SwitchContainer::create_element(const litehtml::tchar_t *tag_name, const litehtml::string_map &attributes, const std::shared_ptr<litehtml::document> &doc)
{ 
	return nullptr;
}

void SwitchContainer::get_media_features(litehtml::media_features& media) const
{ 
	// may need adjustment aswell
	litehtml::position client;
	get_client_rect(client);

	// Fill with switch dimensions, and other hardware details.
	media.type = litehtml::media_type::media_type_screen; // could be handheld instead of screen.
	media.width = client.width;
	media.height = client.height;
	media.device_width = client.width;
	media.device_height = client.height;
	media.color = 8; // might be 16 or 32 need to investigate.
	media.color_index = 256; // ??? might be 255 iono
	media.monochrome = 0;
	media.resolution = SWITCH_PPI;
}

void SwitchContainer::get_language(litehtml::tstring& language, litehtml::tstring& culture) const
{ 
	language = "en";
	culture = "";
}

litehtml::tstring SwitchContainer::resolve_color(const litehtml::tstring& color) const
{ 
	// this might be used not sure yet, no docs online.

	return "";
}