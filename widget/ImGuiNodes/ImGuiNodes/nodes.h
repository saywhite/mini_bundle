#pragma once

#include "imgui.h"
#include "imgui_internal.h"

namespace ImGui
{
	////////////////////////////////////////////////////////////////////////////////

	enum ImGuiNodesConnectorType_
	{
		ImGuiNodesConnectorType_None = 0,
		ImGuiNodesConnectorType_Generic,
		ImGuiNodesConnectorType_Int,
		ImGuiNodesConnectorType_Float, 
		ImGuiNodesConnectorType_Vector,
		ImGuiNodesConnectorType_Image,
		ImGuiNodesConnectorType_Text
	};

	enum ImGuiNodesNodeType_
	{
		ImGuiNodesNodeType_None = 0,
		ImGuiNodesNodeType_Generic,
		ImGuiNodesNodeType_Generator,
		ImGuiNodesNodeType_Test
	};

	enum ImGuiNodesConnectorStateFlag_
	{
		ImGuiNodesConnectorStateFlag_Default	= 0,
		ImGuiNodesConnectorStateFlag_Visible	= 1 << 0,
		ImGuiNodesConnectorStateFlag_Hovered	= 1 << 1,
		ImGuiNodesConnectorStateFlag_Consider	= 1 << 2,
		ImGuiNodesConnectorStateFlag_Draging	= 1 << 3
	};

	enum ImGuiNodesNodeStateFlag_
	{
		ImGuiNodesNodeStateFlag_Default			= 0,
		ImGuiNodesNodeStateFlag_Visible			= 1 << 0,
		ImGuiNodesNodeStateFlag_Hovered			= 1 << 1,
		ImGuiNodesNodeStateFlag_Marked			= 1 << 2,
		ImGuiNodesNodeStateFlag_Selected		= 1 << 3,
		ImGuiNodesNodeStateFlag_Collapsed		= 1 << 4,
		ImGuiNodesNodeStateFlag_Disabled		= 1 << 5,
		ImGuiNodesNodeStateFlag_Processing		= 1 << 6 
	};

	enum ImGuiNodesState_
	{
		ImGuiNodesState_Default	= 0,
		ImGuiNodesState_HoveringNode,
		ImGuiNodesState_HoveringInput,
		ImGuiNodesState_HoveringOutput,
		ImGuiNodesState_Draging,
		ImGuiNodesState_DragingInput,
		ImGuiNodesState_DragingOutput,
		ImGuiNodesState_Selecting
	};

	////////////////////////////////////////////////////////////////////////////////

	typedef unsigned int ImGuiNodesConnectorType;
	typedef unsigned int ImGuiNodesNodeType;

	typedef unsigned int ImGuiNodesConnectorState;
	typedef unsigned int ImGuiNodesNodeState;

	typedef unsigned int ImGuiNodesState;

	////////////////////////////////////////////////////////////////////////////////

	// connector text name heights factors
	constexpr float ImGuiNodesConnectorDotDiameter = 0.7f; // connectors dot diameter
	constexpr float ImGuiNodesConnectorDotPadding = 0.35f; // connectors dot left/right sides padding
	constexpr float ImGuiNodesConnectorDistance = 1.5f; // vertical distance between connectors centers
	
	// title text name heights factors
	constexpr float ImGuiNodesHSeparation = 1.7f; // extra horizontal separation inbetween IOs
	constexpr float ImGuiNodesVSeparation = 1.5f; // total IOs area separation from title and node bottom edge
	constexpr float ImGuiNodesTitleHight = 2.0f;

	//ImGuiNodesConnectionDesc size round up to 32 bytes to be cache boundaries friendly
	constexpr int ImGuiNodesNamesMaxLen = 32 - sizeof(ImGuiNodesConnectorType);

	struct ImGuiNodesConnectionDesc
	{
		char name_[ImGuiNodesNamesMaxLen];
		ImGuiNodesConnectorType type_;
	};

	//TODO: ImVector me
	/*
		If the number of initializer clauses is less than the number of members and bases (since C++17) or initializer list is completely empty, 
		the remaining members and bases (since C++17) are initialized by their default member initializers, if provided in the class definition, 
		and otherwise (since C++14) copy-initialized from empty lists, in accordance with the usual list-initialization rules (which performs 
		value-initialization for non-class types and 
		non-aggregate classes with default constructors, and 
		aggregate initialization for aggregates).

    	inline ImVector()                                       { Size = Capacity = 0; Data = NULL; }
    	inline ImVector(const ImVector<T>& src)                 { Size = Capacity = 0; Data = NULL; operator=(src); }
    	inline ImVector<T>& operator=(const ImVector<T>& src)   { clear(); resize(src.Size); if (src.Data) memcpy(Data, src.Data, (size_t)Size * sizeof(T)); return *this; }
	*/
	struct ImGuiNodesNodeDesc
	{
		char name_[ImGuiNodesNamesMaxLen];
		ImGuiNodesNodeType type_;
		ImColor color_;
		ImVector<ImGuiNodesConnectionDesc> inputs_;
		ImVector<ImGuiNodesConnectionDesc> outputs_;
		ImGuiNodesNodeDesc(char const *NodeName, ImGuiNodesNodeType NodeType, ImColor NodeColor) : name_(NodeName), type_(NodeType), color_(NodeColor) {}
	};

	////////////////////////////////////////////////////////////////////////////////
	struct ImGuiNodesNode;
	struct ImGuiNodesInput;
	struct ImGuiNodesOutput;
	struct ImGuiNodes;

	struct ImGuiNodesInput
	{
		ImVec2 pos_;
		ImRect area_input_;
		ImRect area_name_;
		ImGuiNodesConnectorType type_;
		ImGuiNodesConnectorState state_;
		const char* name_;
		ImGuiNodesNode* target_;
		ImGuiNodesOutput* output_;

		inline void TranslateInput(ImVec2 delta);
		inline void DrawInput(ImDrawList* draw_list, ImVec2 offset, float scale, ImGuiNodesState state) const;

		ImGuiNodesInput(const char* name, ImGuiNodesConnectorType type);
	};

	struct ImGuiNodesOutput
	{
		ImVec2 pos_;
		ImRect area_output_;
		ImRect area_name_;
		ImGuiNodesConnectorType type_;
		ImGuiNodesConnectorState state_;
		const char* name_;
		unsigned int connections_;

		inline void TranslateOutput(ImVec2 delta);
		inline void DrawOutput(ImDrawList* draw_list, ImVec2 offset, float scale, ImGuiNodesState state) const;

		ImGuiNodesOutput(const char* name, ImGuiNodesConnectorType type);
	};

	struct ImGuiNodesNode
	{
		ImRect area_node_;
		ImRect area_name_;
		float title_height_;
		float body_height_;
		ImGuiNodesNodeState state_;
		ImGuiNodesNodeType type_;
		const char* name_;
		ImColor color_;
		ImVector<ImGuiNodesInput> inputs_;
		ImVector<ImGuiNodesOutput> outputs_;

		inline void TranslateNode(ImVec2 delta, bool selected_only = false);
		inline void BuildNodeGeometry(ImVec2 inputs_size, ImVec2 outputs_size);
		inline void DrawNode(ImDrawList* draw_list, ImVec2 offset, float scale, ImGuiNodesState state) const;

		ImGuiNodesNode(const char* name, ImGuiNodesNodeType type, ImColor color);
	};

	struct ImGuiNodes
	{
	private:
		ImVec2 mouse_;
		ImVec2 pos_;
		ImVec2 size_;
		ImVec2 scroll_;
		ImVec4 connection_;
		float scale_;

		////////////////////////////////////////////////////////////////////////////////

		ImGuiNodesState state_;

		ImRect area_;
		ImGuiNodesNode* element_node_ = NULL;
		ImGuiNodesInput* element_input_ = NULL;
		ImGuiNodesOutput* element_output_ = NULL;
		ImGuiNodesNode* processing_node_ = NULL;

		////////////////////////////////////////////////////////////////////////////////

		ImVector<ImGuiNodesNode*> nodes_;
		ImVector<ImGuiNodesNodeDesc> nodes_desc_;

		////////////////////////////////////////////////////////////////////////////////
	
	private:
		void UpdateCanvasGeometry(ImDrawList* draw_list);
		ImGuiNodesNode* UpdateNodesFromCanvas();
		ImGuiNodesNode* CreateNodeFromDesc(ImGuiNodesNodeDesc* desc, ImVec2 pos);

		inline void DrawConnection(ImVec2 p1, ImVec2 p4, ImColor color);
		inline bool ConnectionMatrix(ImGuiNodesNode* input_node, ImGuiNodesNode* output_node, ImGuiNodesInput* input, ImGuiNodesOutput* output);
		inline bool SortSelectedNodesOrder();

	public:
		void Update();
		void ProcessNodes();
		void ProcessContextMenu();

		ImGuiNodes()
		{
			scale_ = 1.0f;
			state_ = ImGuiNodesState_Default;
			element_node_ = NULL;
			element_input_ = NULL;
			element_output_ = NULL;

			////////////////////////////////////////////////////////////////////////////////

			{
				// in ths case, inputs_ and outputs_ should been copy-initialized by their default constructors
				ImGuiNodesNodeDesc desc("Test", ImGuiNodesNodeType_Generic, ImColor(0.2, 0.3, 0.6, 0.0f));
				nodes_desc_.push_back(desc);
			
				desc.inputs_.push_back({ "Float", ImGuiNodesConnectorType_Float });
				desc.inputs_.push_back({ "Int", ImGuiNodesConnectorType_Int });
				desc.inputs_.push_back({ "TextStream", ImGuiNodesConnectorType_Text });
				
				desc.outputs_.push_back({ "Float", ImGuiNodesConnectorType_Float });
				
				auto& back = nodes_desc_.back();
				back.inputs_ = desc.inputs_;
				back.outputs_ = desc.outputs_;
			}

			{
				ImGuiNodesNodeDesc desc("InputBox", ImGuiNodesNodeType_Generic, ImColor(0.3, 0.5, 0.5, 0.0f));
				nodes_desc_.push_back(desc);
			
				desc.inputs_.push_back({ "Float1", ImGuiNodesConnectorType_Float });
				desc.inputs_.push_back({ "Float2", ImGuiNodesConnectorType_Float });
				desc.inputs_.push_back({ "Int1", ImGuiNodesConnectorType_Int });
				desc.inputs_.push_back({ "Int2", ImGuiNodesConnectorType_Int });
				desc.inputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.inputs_.push_back({ "GenericSink", ImGuiNodesConnectorType_Generic });
				desc.inputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.inputs_.push_back({ "Vector", ImGuiNodesConnectorType_Vector });
				desc.inputs_.push_back({ "Image", ImGuiNodesConnectorType_Image });
				desc.inputs_.push_back({ "Text", ImGuiNodesConnectorType_Text });
			
				desc.outputs_.push_back({ "TextStream", ImGuiNodesConnectorType_Text });
				desc.outputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.outputs_.push_back({ "Float", ImGuiNodesConnectorType_Float });
				desc.outputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.outputs_.push_back({ "Int", ImGuiNodesConnectorType_Int });
			
				auto& back = nodes_desc_.back();
				back.inputs_.swap(desc.inputs_);
				back.outputs_.swap(desc.outputs_);
			}
			
			{
				ImGuiNodesNodeDesc desc("OutputBox", ImGuiNodesNodeType_Generic, ImColor(0.4, 0.3, 0.5, 0.0f));
				nodes_desc_.push_back(desc);
			
				desc.inputs_.push_back({ "GenericSink1", ImGuiNodesConnectorType_Generic });
				desc.inputs_.push_back({ "GenericSink2", ImGuiNodesConnectorType_Generic });
				desc.inputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.inputs_.push_back({ "Float", ImGuiNodesConnectorType_Float });
				desc.inputs_.push_back({ "Int", ImGuiNodesConnectorType_Int });
				desc.inputs_.push_back({ "Text", ImGuiNodesConnectorType_Text });
			
				desc.outputs_.push_back({ "Vector", ImGuiNodesConnectorType_Vector });
				desc.outputs_.push_back({ "Image", ImGuiNodesConnectorType_Image });
				desc.outputs_.push_back({ "Text", ImGuiNodesConnectorType_Text });
				desc.outputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.outputs_.push_back({ "Float", ImGuiNodesConnectorType_Float });
				desc.outputs_.push_back({ "Int", ImGuiNodesConnectorType_Int });
				desc.outputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.outputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.outputs_.push_back({ "", ImGuiNodesConnectorType_None });
				desc.outputs_.push_back({ "Generic", ImGuiNodesConnectorType_Generic });
			
				auto& back = nodes_desc_.back();
				back.inputs_.swap(desc.inputs_);
				back.outputs_.swap(desc.outputs_);
			}

			////////////////////////////////////////////////////////////////////////////////

			return;
		}

		~ImGuiNodes()
		{
			for (int desc_idx = 0; desc_idx < nodes_desc_.size(); ++desc_idx)
			{
				ImGuiNodesNodeDesc& node = nodes_desc_[desc_idx];

				node.inputs_.~ImVector();
				node.outputs_.~ImVector();
			}
			
			for (int node_idx = 0; node_idx < nodes_.size(); ++node_idx)
				delete nodes_[node_idx];
		}
	};


	////////////////////////////////////////////////////////////////////////////////
}