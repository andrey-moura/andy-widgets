#include <iostream>

#include <andy/widgets/layout.hpp>

#include <andy/file.hpp>
#include <andy/drawing/image.hpp>
#include <andy/xml.hpp>

#include <andy/tests.hpp>

using namespace andy::tests;

describe of(structure, "andy::widgets::layout", []() {
    it("should be flexible by default", [](){
        andy::widgets::layout l;
        expect(l.style_layout.type).to<eq>(andy::widgets::layout_style::layout_type::flexible);
    });

    describe("childreans", [](){
        it("should be empty by default", [](){
            andy::widgets::layout l;
            expect(l.childreans.size()).to<eq>(0);
        });
    });

    describe("flexible", [](){
        it("should have a vertical direction by default", [](){
            andy::widgets::layout l;
            expect(l.style_layout.direction).to<eq>(andy::widgets::layout_style::layout_flex_direction::vertical);
        });

        auto flexible_describer = [](andy::widgets::layout_style::layout_flex_direction direction) {
            const char* directions[] = {
                "vertical",
                "horizontal"
            };
            describe(directions[(int)direction], [direction]() {

                auto create_layout = [](andy::widgets::layout_style::layout_flex_direction direction, int x, int y, int w, int h, int childreans = 0, andy::widgets::widget c = {}) {
                    andy::widgets::layout l;
                    l.style_layout.direction = direction;
                    l.x = x;
                    l.y = y;
                    l.w = w;
                    l.h = h;
                    
                    for(int i = 0; i < childreans; i++) {
                        l.childreans.push_back(std::make_shared<andy::widgets::widget>(c));
                    }

                    return l;
                };

                it("should correctly position it's childreans", [=](){
                    andy::widgets::layout l = create_layout(direction, 0, 0, 400, 400, 10, {0, 0, 10, 10});
                    l.calculate_layout(0, 0, 400, 400);

                    for(int i = 0; i < 10; i++) {
                        int flexible_attribute = direction == andy::widgets::layout_style::layout_flex_direction::vertical ? l.childreans[i]->y : l.childreans[i]->x;
                        int fixed_attribute = direction == andy::widgets::layout_style::layout_flex_direction::vertical ? l.childreans[i]->x : l.childreans[i]->y;

                        expect(flexible_attribute).to<eq>(10 * i);
                        expect(fixed_attribute).to<eq>(0);
                    }
                });
                it("should update childreans width/height based on direction", [direction](){
                    andy::widgets::layout l;

                    l.style_layout.direction = direction;

                    for(int i = 0; i < 10; i++) {
                        l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 0, 0));
                    }
                    
                    l.calculate_layout(0, 0, 400, 400);

                    for(int i = 0; i < 10; i++) {
                        int space = direction == andy::widgets::layout_style::layout_flex_direction::vertical ? l.childreans[i]->w : l.childreans[i]->h;
                        expect(space).to<eq>(400);
                    }
                });
                it("should align items in center correctly", [direction](){
                    andy::widgets::layout l;
                    l.style_layout.align_items = andy::widgets::layout_style::layout_align_items::center;
                    l.style_layout.direction = direction;

                    l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10));
                    l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10));

                    l.calculate_layout(0, 0, 400, 400);

                    expect(direction == andy::widgets::layout_style::layout_flex_direction::vertical ? l.childreans[0]->y : l.childreans[0]->x).to<eq>(190);
                    expect(direction == andy::widgets::layout_style::layout_flex_direction::vertical ? l.childreans[1]->y : l.childreans[1]->x).to<eq>(200);
                });
                it("should align items in end correctly", [direction](){
                    andy::widgets::layout l;
                    l.style_layout.align_items = andy::widgets::layout_style::layout_align_items::end;
                    l.style_layout.direction = direction;

                    l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10));
                    l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10));

                    l.calculate_layout(0, 0, 400, 400);

                    expect(direction == andy::widgets::layout_style::layout_flex_direction::vertical ? l.childreans[0]->y : l.childreans[0]->x).to<eq>(380);
                    expect(direction == andy::widgets::layout_style::layout_flex_direction::vertical ? l.childreans[1]->y : l.childreans[1]->x).to<eq>(390);
                });
            });
        };

        flexible_describer(andy::widgets::layout_style::layout_flex_direction::vertical);
        flexible_describer(andy::widgets::layout_style::layout_flex_direction::horizontal);

        describe("old", [](){

            it("should not update childreans height", [](){
                andy::widgets::layout l;

                l.style_layout.direction = andy::widgets::layout_style::layout_flex_direction::vertical;

                for(int i = 0; i < 10; i++) {
                    l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10));
                }
                
                l.calculate_layout(0, 0, 400, 400);

                for(int i = 0; i < 10; i++) {
                    expect(l.childreans[i]->h).to<eq>(10);
                }
            });

            it("should divide size equally on spacers elements", [](){
                andy::widgets::layout l;

                l.style_layout.direction = andy::widgets::layout_style::layout_flex_direction::vertical;

                for(int i = 0; i < 3; i++) {
                    l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10, andy::widgets::widget_style(1) ));
                }
                
                l.calculate_layout(0, 0, 400, 400);

                for(int i = 0; i < 3; i++) {
                    expect(l.childreans[i]->h).to<eq>(400 / 3);
                }
            });

            it("should divide size accordily to the spacer elements", [](){
                andy::widgets::layout l;

                l.style_layout.direction = andy::widgets::layout_style::layout_flex_direction::vertical;

                l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10, andy::widgets::widget_style(1) ));
                l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10, andy::widgets::widget_style(1) ));
                l.childreans.push_back(std::make_shared<andy::widgets::widget>(0, 0, 10, 10, andy::widgets::widget_style(2) ));
                
                l.calculate_layout(0, 0, 400, 400);

                expect(l.childreans[0]->h).to<eq>(100);
                expect(l.childreans[1]->h).to<eq>(100);
                expect(l.childreans[2]->h).to<eq>(200);
            });
        });
    });

    describe(".render", [](){
        std::filesystem::path widgets_folder = std::filesystem::current_path() / "include" / "andy-widgets";
        std::filesystem::path flex_folder = widgets_folder / "andy-tests" / "andy-widgets" / "render" / "layout" / "flex";

        auto xml_renderer_describer = [&](std::string_view filename) {
            it("should render {}.xml correctly", {filename}, [&](){
                std::filesystem::path file = flex_folder / filename;
                file.replace_extension(".bmp");

                andy::drawing::image img = andy::drawing::image::load_bitmap(file);

                file.replace_extension(".xml");

                andy::xml xml = andy::xml::decode(andy::file::read_all_text<char>(file));
                andy::xml::schema schema = andy::xml::decode(andy::file::read_all_text<char>(widgets_folder / "schema.xsd"));

                andy::drawing::memory_surface surface(img.size());
                andy::drawing::software_renderer renderer(surface);

                andy::widgets::layout l;
                l.parse(renderer, schema, xml);

                l.calculate_layout(0, 0, img.size().w, img.size().h);
                l.render(renderer);

                andy::drawing::image img2 = surface.to_image();

                std::filesystem::path output_path = std::filesystem::current_path() / "build" / filename;
                output_path.replace_extension(".bmp");

                img2.save_bitmap(output_path);

                expect(img2).to<eq>(img);

                andy::drawing::image testimg(andy::size(400, 400));

                testimg.fill(andy::color(255, 0, 0, 255), andy::rect(0, 0, 133, 400));
                testimg.fill(andy::color(0, 255, 0, 255), andy::rect(133, 0, 133, 400));
                testimg.fill(andy::color(0, 0, 255, 255), andy::rect(266, 0, 134, 400));

                testimg.save_bitmap("test.bmp");
            });
        };

        int i = 1;
        while(true) {
            if(std::filesystem::exists(flex_folder / (std::to_string(i) + ".xml"))) {
                xml_renderer_describer(std::to_string(i));
            } else {
                break;
            }
            i++;
        }
    });
});