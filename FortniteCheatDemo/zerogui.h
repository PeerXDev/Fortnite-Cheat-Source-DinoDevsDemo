#include <string>
#include <wtypes.h>
#include "Imgui/imgui.h"
#include "skStr.h"
#define ZeroGUI_MIN(A, B)            (((A) < (B)) ? (A) : (B))
#define ZeroGUI_MAX(A, B)            (((A) >= (B)) ? (A) : (B))

namespace ZeroGui
{
	namespace Input
	{
		static bool mouseDown[5];
		static bool mouseDownAlready[256];

		static bool is_mouse_clicked(int button, int element_id, bool repeat)
		{
			if (mouseDown[button])
			{
				if (!mouseDownAlready[element_id])
				{
					mouseDownAlready[element_id] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				mouseDownAlready[element_id] = false;
			}
			return false;
		}
	}

	namespace MenuColors
	{
		ImColor Text = IM_COL32(255, 255, 255, 255);
		ImColor Text_Shadow = IM_COL32(255, 255, 255, 255);

		ImColor Window_Background = IM_COL32(0, 0, 0, 255);
		ImColor Window_Header = IM_COL32(255, 0, 0, 255);

		ImColor Button_Idle = IM_COL32(127.5, 0, 0, 255);
		ImColor Button_Hovered = IM_COL32(127.5, 0, 0, 255);
		ImColor Button_Active = IM_COL32(255, 0, 0, 255);

		ImColor Checkbox_Idle = IM_COL32(255, 255, 255, 255);
		ImColor Checkbox_Hovered = IM_COL32(255, 255, 255, 255);
		ImColor Checkbox_Enabled = IM_COL32(255, 0, 0, 255);

		ImColor Slider_Idle = IM_COL32(255, 255, 255, 255);
		ImColor Slider_Hovered = IM_COL32(12.75, 12.75, 12.75, 255);
		ImColor Slider_Button = IM_COL32(0.10f, 0.15f, 0.84f, 1.0f);
		ImColor Slider_Progress = IM_COL32(255, 0, 0, 255);

		ImColor ColorPicker_Background = IM_COL32(1.53, 1.53, 1.53, 255);

		ImColor ESPColor = IM_COL32(255, 0, 0, 255);
	}

	namespace PostRenderer
	{
		struct DrawList
		{
			int type = -1; //1 = FilledRect, 2 = text_left, 3 = text_center, 4 = draw_line

			ImVec2 pos;
			ImVec2 size;

			ImColor color;

			char* name;
			bool outline;

			ImVec2 from;
			ImVec2 to;

			int thickness;
		};

		static DrawList drawlist[128];

		static void draw_filled_rect(ImVec2 pos, float w, float h, ImColor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 1;
					drawlist[i].pos = pos;
					drawlist[i].size = ImVec2(w, h);
					drawlist[i].color = color;
					return;
				}
			}
		}

		static void text_left(char* name, ImVec2 pos, ImColor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 2;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}

		static void text_center(char* name, ImVec2 pos, ImColor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 3;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}

		static void draw_line(ImVec2 from, ImVec2 to, int thickness, ImColor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 4;
					drawlist[i].from = from;
					drawlist[i].to = to;
					drawlist[i].thickness = thickness;
					drawlist[i].color = color;
					return;
				}
			}
		}
	}

	static bool hover_element = false;

	static ImVec2 menu_pos = ImVec2(300, 100);

	static float offset_x = 0.0f;
	static float offset_y = 0.0f;

	static ImVec2 first_element_pos = ImVec2(0, 0);

	static ImVec2 last_element_pos = ImVec2(0, 0);
	static ImVec2 last_element_size = ImVec2(0, 0);

	static int current_element = -1;

	static ImVec2 current_element_pos = ImVec2(0, 0);
	static ImVec2 current_element_size = ImVec2(0, 0);

	static int elements_count = 0;

	static bool sameLine = false;

	static bool pushY = false;
	static float pushYvalue = 0.0f;

	static ImVec2 cursor_pos()
	{
		POINT p;
		GetCursorPos(&p);
		return ImVec2((float)p.x, (float)p.y);
	}

	static bool mouse_in_zone(ImVec2 pos, ImVec2 size)
	{
		ImVec2 cursorPos = cursor_pos();

		if (cursorPos.x > pos.x && cursorPos.y > pos.y)
			if (cursorPos.x < pos.x + size.x && cursorPos.y < pos.y + size.y)
				return true;

		return false;
	}

	static void next_column(float x)
	{
		pushY = true;

		offset_x = x;
		offset_y = first_element_pos.y;

		pushYvalue = first_element_pos.y;
	}

	static void push_element_x(float value)
	{
		offset_x = value;
	}

	static void push_element_y(float value)
	{
		pushY = true;
		pushYvalue = menu_pos.y + value - 10;
	}

	static void text_left(char* name, ImVec2 pos, ImColor color)
	{
		ImVec2 DistanceTextSize = ImGui::CalcTextSize(name);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(pos.x, pos.y - DistanceTextSize.y / 2), MenuColors::Text_Shadow, std::string(name).c_str());
	}

	static void text_center(char* name, ImVec2 pos, ImColor color)
	{
		ImVec2 DistanceTextSize = ImGui::CalcTextSize(name);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(pos.x + 1 - DistanceTextSize.x / 2, pos.y + 1 - DistanceTextSize.y / 2), MenuColors::Text_Shadow, std::string(name).c_str());
	}

	static void draw_line(ImVec2 from, ImVec2 to, int thickness, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);
	}

	static void draw_filled_rect(ImVec2 initial_pos, float w, float h, ImColor color)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
		{
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(initial_pos.x, initial_pos.y + i), ImVec2(initial_pos.x + w, initial_pos.y + i), color, 1.0f);
		}
	}
	static void draw_circle(ImVec2 pos, int radius, int numSides, ImColor Color)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(pos.x, pos.y), radius, IM_COL32(255, 255, 255, 255), numSides);
	}

	static ImVec2 dragPos;
	static bool begin_window(char* name, ImVec2 pos, ImVec2 size, bool IsOpen, bool WindowInvisible)
	{
		elements_count = 0;

		if (!IsOpen)
		{
			return false;
		}

		bool isHovered = mouse_in_zone(ImVec2(pos.x, pos.y), size);

		//Drop last element
		if (current_element != -1 && !ZeroGui::Input::mouseDown[0] || ZeroGui::Input::mouseDown[1])
		{
			current_element = -1;
		}

		//Drag
		if (hover_element && ZeroGui::Input::mouseDown[0] || ZeroGui::Input::mouseDown[1])
		{

		}

		else if ((isHovered || dragPos.x != 0) && !hover_element)
		{
			if (Input::is_mouse_clicked(0, elements_count, true))
			{
				ImVec2 cursorPos = cursor_pos();

				cursorPos.x -= size.x;
				cursorPos.y -= size.y;

				if (dragPos.x == 0)
				{
					dragPos.x = (cursorPos.x - pos.x);
					dragPos.y = (cursorPos.y - pos.y);
				}
				pos.x = cursorPos.x - dragPos.x;
				pos.y = cursorPos.y - dragPos.y;
			}
			else
			{
				dragPos = ImVec2(0, 0);
			}
		}
		else
		{
			hover_element = false;
		}

		offset_x = 0.0f; offset_y = 0.0f;

		menu_pos = ImVec2(pos.x, pos.y);

		first_element_pos = ImVec2(0, 0);
		current_element_pos = ImVec2(0, 0);
		current_element_size = ImVec2(0, 0);

		if (!WindowInvisible)
		{
			//Bg
			draw_filled_rect(ImVec2(pos.x, pos.y), size.x, size.y, MenuColors::Window_Background);

			//Header
			draw_filled_rect(ImVec2(pos.x, pos.y), size.x, 25.0f, MenuColors::Window_Header);

			offset_y += 25.0f;

			//Title
			ImVec2 titlePos = ImVec2(pos.x + size.x / 2, pos.y + 25 / 2);
			text_center(name, titlePos, IM_COL32(255, 255, 255, 255));
		}
		else
		{
			offset_y += 25.0f;
		}

		return true;
	}

	static void text_normal(char* text, bool center = false, bool outline = false)
	{
		elements_count++;

		float size = 25;
		ImVec2 padding = ImVec2(10, 10);
		ImVec2 pos = ImVec2(menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y);
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		if (!sameLine)
			offset_y += size + padding.y;

		//Text
		ImVec2 textPos = ImVec2(pos.x + 5.0f, pos.y + size / 2);
		if (center)
			text_center(text, textPos, IM_COL32(255, 255, 255, 255));
		else
			text_left(text, textPos, IM_COL32(255, 255, 255, 255));

		sameLine = false;
		last_element_pos = pos;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	static bool button_tab(char* name, ImVec2 size, bool active)
	{
		elements_count++;

		ImVec2 padding = ImVec2(5, 10);
		ImVec2 pos = ImVec2(menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y);
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(ImVec2(pos.x, pos.y), size);

		//Bg
		if (active)
		{
			draw_filled_rect(ImVec2(pos.x - 1, pos.y - 1), size.x + 2, size.y + 2, IM_COL32(255, 255, 255, 255));
			draw_filled_rect(ImVec2(pos.x, pos.y), size.x, size.y, MenuColors::Button_Active);
		}
		else if (isHovered)
		{
			draw_filled_rect(ImVec2(pos.x - 1, pos.y - 1), size.x + 2, size.y + 2, IM_COL32(255, 255, 255, 255));
			draw_filled_rect(ImVec2(pos.x, pos.y), size.x, size.y, MenuColors::Button_Hovered);

			hover_element = true;
		}
		else
		{
			draw_filled_rect(ImVec2(pos.x - 1, pos.y - 1), size.x + 2, size.y + 2, IM_COL32(255, 255, 255, 255));
			draw_filled_rect(ImVec2(pos.x, pos.y), size.x, size.y, MenuColors::Button_Idle);
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		ImVec2 textPos = ImVec2(pos.x + size.x / 2, pos.y + size.y / 2);
		text_center(name, textPos, IM_COL32(255, 255, 255, 255));


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::is_mouse_clicked(0, elements_count, false))
			return true;

		return false;
	}

	static void check_box(char* name, bool* value)
	{
		elements_count++;

		float size = 18;
		ImVec2 padding = ImVec2(10, 10);
		ImVec2 pos = ImVec2(menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y);

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}

		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = mouse_in_zone(ImVec2(pos.x, pos.y), ImVec2(size, size));

		//Bg
		if (isHovered)
		{
			draw_filled_rect(ImVec2(pos.x, pos.y), size, size, MenuColors::Checkbox_Hovered);
			hover_element = true;
		}
		else
		{
			draw_filled_rect(ImVec2(pos.x, pos.y), size, size, MenuColors::Checkbox_Idle);
		}

		if (!sameLine)
		{
			offset_y += size + padding.y;
		}

		if (*value)
		{
			draw_filled_rect(ImVec2(pos.x + 3, pos.y + 3), size - 6, size - 6, MenuColors::Checkbox_Enabled);
		}

		//Text
		ImVec2 textPos = ImVec2(pos.x + size + 5.0f, pos.y + size / 2);
		text_left(name, textPos, IM_COL32(255, 255, 255, 255));

		sameLine = false;
		last_element_pos = pos;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::is_mouse_clicked(0, elements_count, false))
			*value = !*value;
	}

	static void zero_slider(char* name, int* value, int min, int max)
	{
		elements_count++;

		ImVec2 size = ImVec2(210, 40);
		ImVec2 slider_size = ImVec2(170, 7);
		ImVec2 adjust_zone = ImVec2(0, 20);
		ImVec2 padding = ImVec2(10, 15);

		ImVec2 pos = ImVec2(menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y);

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(ImVec2(pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y), ImVec2(slider_size.x, slider_size.y + adjust_zone.y * 1.5f));

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Bg
		if (isHovered || current_element == elements_count)
		{
			//Drag
			if (Input::is_mouse_clicked(0, elements_count, true))
			{
				current_element = elements_count;

				ImVec2 cursorPos = cursor_pos();
				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			hover_element = true;
		}

		//Text
		ImVec2 textPos = ImVec2(pos.x, pos.y + 5);
		text_left(name, textPos, MenuColors::Text);

		//Empty
		float oneP = slider_size.x / (max - min);
		draw_filled_rect(ImVec2(pos.x, pos.y + slider_size.y + padding.y), slider_size.x, slider_size.y, MenuColors::Slider_Idle);

		//Value
		draw_filled_rect(ImVec2(pos.x, pos.y + slider_size.y + padding.y), oneP * (*value - min), slider_size.y, MenuColors::Slider_Progress);

		ImVec2 valuePos = ImVec2(pos.x + oneP * (*value - min), pos.y + slider_size.y + 25 + padding.y);

		if (*value != 0)
		{
			text_center((char*)std::to_string(*value).c_str(), valuePos, IM_COL32(255, 255, 255, 255));
		}
		else
		{
			text_center(_("0"), valuePos, IM_COL32(255, 255, 255, 255));
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	static void zero_render()
	{
		for (int i = 0; i < 128; i++)
		{
			if (PostRenderer::drawlist[i].type != -1)
			{
				//filled_Rect
				if (PostRenderer::drawlist[i].type == 1)
				{
					ZeroGui::draw_filled_rect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.x, PostRenderer::drawlist[i].size.y, PostRenderer::drawlist[i].color);
				}

				//text_left
				else if (PostRenderer::drawlist[i].type == 2)
				{
					ZeroGui::text_left(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color);
				}

				//text_center
				else if (PostRenderer::drawlist[i].type == 3)
				{
					ZeroGui::text_center(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color);
				}

				//draw_line
				else if (PostRenderer::drawlist[i].type == 4)
				{
					draw_line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
				}

				PostRenderer::drawlist[i].type = -1;
			}
		}
	}
}