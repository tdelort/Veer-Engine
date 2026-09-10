#pragma once

#include <core/core.h>
#include <display/render/shader_source.h>

namespace veer::display::render
{
    struct shader_parameter_id
    {
        // Root Signature param index on D3D12 basically
    };

    class technique
    {
    public:
        shader_parameter_id get_param_id(const char* _param_name);
    };

    class graphics_technique : public technique
    {
    public:
        graphics_technique(const shader_stage_source_container_t& _source_code, const shader_signature& _signature,
                           const shader_render_state& _render_state);
        virtual ~graphics_technique();
    };

    class compute_technique : public technique
    {
    public:
        compute_technique(const shader_stage_source_container_t& _source_code);
        virtual ~compute_technique();
    };
} // namespace veer::display::render