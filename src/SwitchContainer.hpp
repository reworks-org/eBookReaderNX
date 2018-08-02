///
/// eBookReaderNX
/// reworks
/// Apache 2.0 License.
///

#ifndef EBRNX_SWITCHCONTAINER_HPP_
#define EBRNX_SWITCHCONTAINER_HPP_

#include "Font.hpp"
#include "libs/litehtml/litehtml.h"

///
/// A class that implements litehtml's document_container used to render HTML and CSS.
///
class SwitchContainer : public litehtml::document_container
{
public:
	///
	/// Destructor.
	///
	~SwitchContainer();

	///
	/// Set the window to use.
	///
	/// \param window Pointer to window to use for rendering methods.
	///
	void setWindow(Window* window);

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	litehtml::uint_ptr create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void delete_font(litehtml::uint_ptr hFont) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	int text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	int pt_to_px(int pt) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	int get_default_font_size() const override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	const litehtml::tchar_t* get_default_font_name() const override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void set_caption(const litehtml::tchar_t* caption) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void set_base_url(const litehtml::tchar_t* base_url) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr& el) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void set_cursor(const litehtml::tchar_t* cursor) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void transform_text(litehtml::tstring& text, litehtml::text_transform tt) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void del_clip() override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void get_client_rect(litehtml::position& client) const override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	std::shared_ptr<litehtml::element> create_element(const litehtml::tchar_t *tag_name, const litehtml::string_map &attributes, const std::shared_ptr<litehtml::document> &doc) override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void get_media_features(litehtml::media_features& media) const override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	void get_language(litehtml::tstring& language, litehtml::tstring& culture) const override;

	///
	/// See: https://github.com/litehtml/litehtml/wiki/document_container
	///
	litehtml::tstring resolve_color(const litehtml::tstring& color) const override;

private:
	///
	/// Pointer to the window object for various rendering stuff.
	///
	Window* m_window;

	///
	///
	/// Keeps tracks of any fonts to ensure they are cleaned up.
	///
	std::vector<Font*> m_fonts;
};

#endif