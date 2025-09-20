#include <andy/widgets/input.hpp>

namespace andy
{
    namespace widgets
    {
        void input::render(andy::drawing::basic_renderer& renderer) {
            widget::render(renderer);

            int __x = x + style.padding;
            int __y = y + style.padding;

            // center vertically

            //andy::size size = renderer.text_extent(content, 12);

            //__y += (h - size.h) / 2;

            //renderer.draw_text(content, { __x, __y }, 12, style.color);
        }

        void input::parse(andy::xml::schema& schema, andy::xml& xml) {
            widget::parse(schema, xml);

            style.color = schema.color_attribute(xml, "color");
        }

        bool input::on_char(char c) {
            // Handle the character input
            content += c;
            return true;
        }

        andy::size input::calculate_min_size(andy::drawing::basic_renderer& renderer) {
            // Calculate the minimum size of the input widget
            return { 0, 24 };
        }
    };
};