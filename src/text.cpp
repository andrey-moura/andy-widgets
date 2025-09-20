#include <andy/widgets/text.hpp>

#include <stdexcept>

andy::widgets::text::text(std::string __content)
    : content(std::move(__content))
{
}

void andy::widgets::text::render(andy::drawing::basic_renderer& renderer)
{
    widget::render(renderer);

    if(content.size()) {
        renderer.draw_text(content, { x, y }, text_style.font, text_style.font_size, false, false);
    }
}

void andy::widgets::text::parse(andy::xml::schema& schema, andy::xml& xml)
{
    widget::parse(schema, xml);
    
    style.color = schema.color_attribute(xml, "color");
    style.cursor = (andy::widgets::widget_cursor)schema.integer_attribute(xml, "cursor");

    text_style.vertical_alignment   = (andy::widgets::text_vertical_alignment)schema.integer_attribute(xml, "vertical-align");
    text_style.horizontal_alignment = (andy::widgets::text_horizontal_alignment)schema.integer_attribute(xml, "horizontal-align");
    text_style.font = schema.string_attribute(xml, "font-family");

    std::string_view font_size = schema.string_attribute(xml, "font-size");

    if(!font_size.ends_with("px")) {
        throw std::runtime_error("font-size must be in pixels");
    }

    font_size.remove_suffix(2);

    for(const char& c : font_size) {
        if(!std::isdigit(c)) {
            throw std::runtime_error("font-size must be a number");
        }
    }

    text_style.font_size = atoi(font_size.data());
}

andy::size andy::widgets::text::calculate_min_size(andy::drawing::basic_renderer& renderer)
{
    return renderer.text_extent(content, text_style.font, text_style.font_size);
}