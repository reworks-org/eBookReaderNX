///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_SWITCHCONTAINER_HPP_
#define EBRNX_SWITCHCONTAINER_HPP_

#include "libs/litehtml/litehtml.h"

///
/// A class that implements litehtml's document_container used to render HTML and CSS.
///
class SwitchContainer : public litehtml::document_container
{
public:
	SwitchContainer();
	~SwitchContainer();

	litehtml::uint_ptr create_font(const tchar_t* faceName, int size, int weight, font_style italic, unsigned int decoration, litehtml::font_metrics* fm override) override;
};

#endif