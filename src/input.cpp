#include <uva/widgets/input.hpp>

namespace uva
{
    namespace widgets
    {
        void input::render(void* target) {
            widget::render(target);

            int __x = x + style.padding;
            int __y = y + style.padding;

            // center vertically

            //uva::size size = renderer.text_extent(content, 12);

            //__y += (h - size.h) / 2;

            //renderer.draw_text(content, { __x, __y }, 12, style.color);
        }

        void input::parse(void* target, uva::xml::schema& schema, uva::xml& xml) {
            widget::parse(target, schema, xml);

            style.color = schema.color_attribute(xml, "color");
        }

        bool input::on_char(std::string c) {
            // Handle the character input
            content += c;
            return true;
        }

        uva::size input::calculate_min_size() {
            // Calculate the minimum size of the input widget
            return { 0, 24 };
        }
    };
};