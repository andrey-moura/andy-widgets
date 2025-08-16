#include <andy/widgets.hpp>

andy::size andy::widgets::layout::calculate_min_size()
{
    int min_w = -1;
    int min_h = -1;

    int& dimension = style_layout.direction == layout_style::layout_flex_direction::vertical ? min_h : min_w;

    for(size_t i = 0; i < childreans.size(); i++) {
        auto& child = childreans[i];
        andy::size s = child->calculate_min_size();

        int child_dimension = style_layout.direction == layout_style::layout_flex_direction::vertical ? s.h : s.w;

        dimension += child_dimension;

        if(i > 0) {
            dimension += style.gap;
        }
    }

    return { min_w, min_h };
}

void andy::widgets::layout::calculate_layout(int __x, int __y, int __w, int __h)
{
    x = __x;
    y = __y;
    w = __w;
    h = __h;

    int current_x = x + style.padding;
    int current_y = y + style.padding;

    int number_of_spacer_elements = 0;
    int available_space = 0;
    int dimension = 0;

    if(style_layout.direction == layout_style::layout_flex_direction::vertical) {
        dimension = h;
    } else {
        dimension = w;
    }
    
    available_space = dimension - (style.padding * 2) - style.gap * childreans.size();

    for(auto& child : childreans) {
        if(child->style.flex > 0) {
            number_of_spacer_elements += child->style.flex;
        } else {
            if(style_layout.direction == layout_style::layout_flex_direction::vertical) {
                available_space -= child->calculate_min_size().h;
            } else {
                available_space -= child->calculate_min_size().h;
            }
        }
    }

    if(number_of_spacer_elements > 0) {
        int available_space_per_spacer = available_space / number_of_spacer_elements;

        for(auto& child : childreans) {
            if(child->style.flex > 0) {
                int child_space = available_space_per_spacer * child->style.flex;

                if(style_layout.direction == layout_style::layout_flex_direction::vertical) {
                    child->h = child_space;
                } else {
                    child->w = child_space;
                }
            }
        }
    } else {
        switch(style_layout.align_items) {
            case layout_style::layout_align_items::center:
                if(style_layout.direction == layout_style::layout_flex_direction::vertical) {
                    current_y += available_space / 2;
                } else {
                    current_x += available_space / 2;
                }
                break;
            case layout_style::layout_align_items::end:
                if(style_layout.direction == layout_style::layout_flex_direction::vertical) {
                    current_y += available_space;
                } else {
                    current_x += available_space;
                }
                break;
            default:
                break;
        }
    }

    for(auto& child : childreans) {
        child->x = current_x;
        child->y = current_y;

        if(style_layout.direction == layout_style::layout_flex_direction::vertical) {
            if(!child->style.flex > 0) {
                child->h = child->calculate_min_size().h;
            }

            child->w = __w - (style.padding * 2);
            current_y += child->h;
            current_y += style.gap;
        } else {
            if(!child->style.flex > 0) {
                child->w = child->calculate_min_size().w;
            }

            child->h = __h - (style.padding * 2);
            current_x += child->w;
            current_x += style.gap;
        }

        layout* le = dynamic_cast<layout*>(child.get());

        if(le) {
            le->calculate_layout(child->x, child->y, child->w, child->h);
        }
    }
}

void andy::widgets::layout::render(void* target)
{
    widget::render(target);

    for(auto& child : childreans) {
        child->render(target);
    }
}

void andy::widgets::layout::parse(void* target, andy::xml::schema& schema, andy::xml& xml)
{
    widget::parse(target, schema, xml);
    
    style_layout.type = (andy::widgets::layout_style::layout_type)schema.integer_attribute(xml, "type");
    style_layout.direction = (andy::widgets::layout_style::layout_flex_direction)schema.integer_attribute(xml, "direction");
    style_layout.align_items = (andy::widgets::layout_style::layout_align_items)schema.integer_attribute(xml, "align");

    for(auto& child : xml.childrens) {
        if(child.tag == "text") {
            std::shared_ptr<andy::widgets::text> te = std::make_shared<andy::widgets::text>();
            te->content = child.content;
            
            te->parse(target, schema, child);

            childreans.push_back(te);
        } else if(child.tag == "layout") {
            std::shared_ptr<andy::widgets::layout> le2 = std::make_shared<andy::widgets::layout>();
            le2->parse(target, schema, child);

            childreans.push_back(le2);
        } else if(child.tag == "input") {
            std::shared_ptr<andy::widgets::input> ie = std::make_shared<andy::widgets::input>();
            ie->parse(target, schema, child);

            childreans.push_back(ie);
        }
    }
}