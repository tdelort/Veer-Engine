#include "submit_context.h"

#include <display/render/command_buffer.h>
#include <display/render/technique.h>

namespace veer::display::render
{
    // compute_submit_context

    compute_submit_context::compute_submit_context(
        compute_command_buffer& _command_buffer, compute_technique& _technique
    )
        : m_command_buffer(_command_buffer)
    {
        m_command_buffer.set_technique(_technique);
    }

    template <arithmetic T>
    void compute_submit_context::set_constant(const shader_parameter_id& _param_id, const T& _val)
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    template <arithmetic T, size_t ELEM_COUNT>
    void compute_submit_context::set_constant(
        const shader_parameter_id& _param_id, const math::vec<T, ELEM_COUNT>& _val
    )
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    void compute_submit_context::set_texture(
        const shader_parameter_id& _param_id, const render_device_texture_base& _texture
    )
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    void compute_submit_context::set_buffer(const shader_parameter_id& _param_id, const render_device_buffer& _buffer)
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    void compute_submit_context::clear_texture(render_device_texture_base& _resource, math::vec4f _val)
    {
        m_command_buffer.transition_barrier(_resource, render_device_resource_sync_state::UnorderedAccessView);
        m_command_buffer.clear_texture(_resource, _val);
    }

    void compute_submit_context::clear_texture(render_device_texture_base& _resource, math::vec4u _val)
    {
        m_command_buffer.transition_barrier(_resource, render_device_resource_sync_state::UnorderedAccessView);
        m_command_buffer.clear_texture(_resource, _val);
    }

    void compute_submit_context::clear_buffer(render_device_buffer& _resource, float _val)
    {
        m_command_buffer.transition_barrier(_resource, render_device_resource_sync_state::UnorderedAccessView);
        m_command_buffer.clear_buffer(_resource, _val);
    }

    void compute_submit_context::clear_buffer(render_device_buffer& _resource, uint32_t _val)
    {
        m_command_buffer.transition_barrier(_resource, render_device_resource_sync_state::UnorderedAccessView);
        m_command_buffer.clear_buffer(_resource, _val);
    }

    void compute_submit_context::dispatch(size_t _x, size_t _y, size_t _z)
    {
        m_command_buffer.dispatch(_x, _y, _z);
    }

    // graphics_submit_context

    graphics_submit_context::graphics_submit_context(
        graphics_command_buffer& _command_buffer, graphics_technique& _technique
    )
        : m_command_buffer(_command_buffer)
        , m_viewports_count(0u)
        , m_scissors_count(0u)
        , m_color_render_outputs_count(0u)
    {
        m_command_buffer.set_technique(_technique);
    }

    template <arithmetic T>
    void graphics_submit_context::set_constant(const shader_parameter_id& _param_id, const T& _val)
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    template <arithmetic T, size_t ELEM_COUNT>
    void graphics_submit_context::set_constant(
        const shader_parameter_id& _param_id, const math::vec<T, ELEM_COUNT>& _val
    )
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    void graphics_submit_context::set_texture(
        const shader_parameter_id& _param_id, const render_device_texture_base& _texture
    )
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    void graphics_submit_context::set_buffer(const shader_parameter_id& _param_id, const render_device_buffer& _buffer)
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    void graphics_submit_context::clear_texture(render_device_texture_base& _resource, math::vec4f _val)
    {
        m_command_buffer.transition_barrier(_resource, render_device_resource_sync_state::UnorderedAccessView);
        m_command_buffer.clear_texture(_resource, _val);
    }

    void graphics_submit_context::clear_texture(render_device_texture_base& _resource, math::vec4u _val)
    {
        m_command_buffer.transition_barrier(_resource, render_device_resource_sync_state::UnorderedAccessView);
        m_command_buffer.clear_texture(_resource, _val);
    }

    void graphics_submit_context::clear_buffer(render_device_buffer& _resource, float _val)
    {
        m_command_buffer.transition_barrier(_resource, render_device_resource_sync_state::UnorderedAccessView);
        m_command_buffer.clear_buffer(_resource, _val);
    }

    void graphics_submit_context::clear_buffer(render_device_buffer& _resource, uint32_t _val)
    {
        m_command_buffer.transition_barrier(_resource, render_device_resource_sync_state::UnorderedAccessView);
        m_command_buffer.clear_buffer(_resource, _val);
    }

    void graphics_submit_context::set_render_output(render_device_texture_2d* _depth, render_device_texture_2d* _color)
    {
        set_render_output(_depth, containers::span<render_device_texture_2d*>(_color));
    }

    void graphics_submit_context::set_render_output(
        render_device_texture_2d* _depth, containers::span<render_device_texture_2d*> _colors
    )
    {
        m_depth_render_output = _depth;

        m_color_render_outputs_count = _colors.size();
        for (size_t i = 0; i < _colors.size(); ++i)
        {
            VEER_ASSERT(_colors[i] != nullptr, "Setting a nullptr render target on graphics submit context");
            m_color_render_outputs[i] = _colors[i];
        }
    }

    void graphics_submit_context::set_viewports(containers::span<viewport> _viewports)
    {
        m_viewports_count = _viewports.size();
        for (size_t i = 0; i < _viewports.size(); ++i)
            m_viewports[i] = _viewports[i];
    }

    void graphics_submit_context::set_scissors(containers::span<rect> _scissor_rects)
    {
        m_scissors_count = _scissor_rects.size();
        for (size_t i = 0; i < _scissor_rects.size(); ++i)
            m_scissors[i] = _scissor_rects[i];
    }

    void graphics_submit_context::clear_render_target(
        render_device_texture_2d& _render_target_resource, math::vec4f _color
    )
    {
        m_command_buffer.transition_barrier(_render_target_resource, render_device_resource_sync_state::RenderTarget);
        m_command_buffer.clear_render_target(_render_target_resource, _color);
    }

    void graphics_submit_context::clear_depth_stencil(
        render_device_texture_2d& _render_target_resource, float _depth, uint8_t _stencil
    )
    {
        m_command_buffer.transition_barrier(_render_target_resource, render_device_resource_sync_state::DepthWrite);
        m_command_buffer.clear_depth_stencil(_render_target_resource, _depth, _stencil);
    }

    void graphics_submit_context::set_mesh(render_device_buffer& _index_buffer, render_device_buffer& _vertex_buffer)
    {
        m_index_buffer = &_index_buffer;
        m_vertex_buffer = &_vertex_buffer;
    }

    void graphics_submit_context::draw_instanced(size_t _vertex_count, size_t _instance_count)
    {
        apply_context();
        m_command_buffer.draw_instanced(_vertex_count, _instance_count);
    }

    void graphics_submit_context::draw_indexed_instanced(size_t _index_count, size_t _instance_count)
    {
        apply_context();
        VEER_ASSERT(m_index_buffer != nullptr, "draw_indexed_instanced called without setting an index buffer");
        m_command_buffer.draw_indexed_instanced(_index_count, _instance_count);
    }

    void graphics_submit_context::draw_indirect(render_device_buffer& _buffer, size_t _arg_index)
    {
        apply_context();
        m_command_buffer.transition_barrier(_buffer, render_device_resource_sync_state::IndirectArgs);
        m_command_buffer.draw_indirect(_buffer, _arg_index);
    }


    void graphics_submit_context::apply_context()
    {
        if (m_depth_render_output)
        {
            // TODO : we need to know if we want DEPTH_READ or DEPTH_WRITE
            // For now, just set as depth write
            m_command_buffer.transition_barrier(*m_depth_render_output, render_device_resource_sync_state::DepthWrite);
        }

        for (size_t i = 0; i < m_color_render_outputs_count; ++i)
        {
            if (m_color_render_outputs[i] == nullptr)
                continue;

            m_command_buffer.transition_barrier(
                *m_color_render_outputs[i], render_device_resource_sync_state::RenderTarget
            );
        }

        m_command_buffer.set_render_output(
            m_depth_render_output,
            containers::span<render_device_texture_2d*>(m_color_render_outputs.data(), m_color_render_outputs_count)
        );

        // For each scissors not specified, use the default one (basically the one
        // encompassing the full viewport)
        for (size_t i = m_scissors_count; i < m_viewports_count; ++i)
        {
            display::render::rect scissor_rect{
                .m_min = m_viewports[i].m_position, .m_max = m_viewports[i].m_position + m_viewports[i].m_size
            };

            m_scissors[i] = scissor_rect;
        }

        m_command_buffer.set_viewports(containers::span<viewport>(m_viewports.data(), m_viewports_count));
        // NOT a typo, m_viewports_count is used since we need to have one scissors
        // rect per viewport The rects from m_scissors_count to m_viewports_count are
        // set in the loop above
        m_command_buffer.set_scissors(containers::span<rect>(m_scissors.data(), m_viewports_count));


        if (m_index_buffer != nullptr)
        {
            m_command_buffer.transition_barrier(*m_index_buffer, render_device_resource_sync_state::IndexBuffer);
            m_command_buffer.set_index_buffer(*m_index_buffer);
        }

        if (m_vertex_buffer != nullptr)
        {
            m_command_buffer.transition_barrier(*m_vertex_buffer, render_device_resource_sync_state::VertexAndConstantBuffer);
            m_command_buffer.set_vertex_buffer(*m_vertex_buffer);
        }
    }

    // "Yandere dev ifelse" ahh explicit template definition
    template void compute_submit_context::set_constant<bool>(const shader_parameter_id&, const bool&);
    template void compute_submit_context::set_constant<int32_t>(const shader_parameter_id&, const int32_t&);
    template void compute_submit_context::set_constant<int64_t>(const shader_parameter_id&, const int64_t&);
    template void compute_submit_context::set_constant<uint32_t>(const shader_parameter_id&, const uint32_t&);
    template void compute_submit_context::set_constant<uint64_t>(const shader_parameter_id&, const uint64_t&);
    template void compute_submit_context::set_constant<float>(const shader_parameter_id&, const float&);
    template void compute_submit_context::set_constant<double>(const shader_parameter_id&, const double&);

    template void compute_submit_context::set_constant<bool, 2>(const shader_parameter_id&, const math::vec<bool, 2>&);
    template void compute_submit_context::set_constant<int32_t, 2>(
        const shader_parameter_id&, const math::vec<int32_t, 2>&
    );
    template void compute_submit_context::set_constant<int64_t, 2>(
        const shader_parameter_id&, const math::vec<int64_t, 2>&
    );
    template void compute_submit_context::set_constant<uint32_t, 2>(
        const shader_parameter_id&, const math::vec<uint32_t, 2>&
    );
    template void compute_submit_context::set_constant<uint64_t, 2>(
        const shader_parameter_id&, const math::vec<uint64_t, 2>&
    );
    template void compute_submit_context::set_constant<float, 2>(
        const shader_parameter_id&, const math::vec<float, 2>&
    );
    template void compute_submit_context::set_constant<double, 2>(
        const shader_parameter_id&, const math::vec<double, 2>&
    );

    template void compute_submit_context::set_constant<bool, 3>(const shader_parameter_id&, const math::vec<bool, 3>&);
    template void compute_submit_context::set_constant<int32_t, 3>(
        const shader_parameter_id&, const math::vec<int32_t, 3>&
    );
    template void compute_submit_context::set_constant<int64_t, 3>(
        const shader_parameter_id&, const math::vec<int64_t, 3>&
    );
    template void compute_submit_context::set_constant<uint32_t, 3>(
        const shader_parameter_id&, const math::vec<uint32_t, 3>&
    );
    template void compute_submit_context::set_constant<uint64_t, 3>(
        const shader_parameter_id&, const math::vec<uint64_t, 3>&
    );
    template void compute_submit_context::set_constant<float, 3>(
        const shader_parameter_id&, const math::vec<float, 3>&
    );
    template void compute_submit_context::set_constant<double, 3>(
        const shader_parameter_id&, const math::vec<double, 3>&
    );

    template void compute_submit_context::set_constant<bool, 4>(const shader_parameter_id&, const math::vec<bool, 4>&);
    template void compute_submit_context::set_constant<int32_t, 4>(
        const shader_parameter_id&, const math::vec<int32_t, 4>&
    );
    template void compute_submit_context::set_constant<int64_t, 4>(
        const shader_parameter_id&, const math::vec<int64_t, 4>&
    );
    template void compute_submit_context::set_constant<uint32_t, 4>(
        const shader_parameter_id&, const math::vec<uint32_t, 4>&
    );
    template void compute_submit_context::set_constant<uint64_t, 4>(
        const shader_parameter_id&, const math::vec<uint64_t, 4>&
    );
    template void compute_submit_context::set_constant<float, 4>(
        const shader_parameter_id&, const math::vec<float, 4>&
    );
    template void compute_submit_context::set_constant<double, 4>(
        const shader_parameter_id&, const math::vec<double, 4>&
    );

    // HERE WE GO AGAIN !!!
    template void graphics_submit_context::set_constant<bool>(const shader_parameter_id&, const bool&);
    template void graphics_submit_context::set_constant<int32_t>(const shader_parameter_id&, const int32_t&);
    template void graphics_submit_context::set_constant<int64_t>(const shader_parameter_id&, const int64_t&);
    template void graphics_submit_context::set_constant<uint32_t>(const shader_parameter_id&, const uint32_t&);
    template void graphics_submit_context::set_constant<uint64_t>(const shader_parameter_id&, const uint64_t&);
    template void graphics_submit_context::set_constant<float>(const shader_parameter_id&, const float&);
    template void graphics_submit_context::set_constant<double>(const shader_parameter_id&, const double&);

    template void graphics_submit_context::set_constant<bool, 2>(const shader_parameter_id&, const math::vec<bool, 2>&);
    template void graphics_submit_context::set_constant<int32_t, 2>(
        const shader_parameter_id&, const math::vec<int32_t, 2>&
    );
    template void graphics_submit_context::set_constant<int64_t, 2>(
        const shader_parameter_id&, const math::vec<int64_t, 2>&
    );
    template void graphics_submit_context::set_constant<uint32_t, 2>(
        const shader_parameter_id&, const math::vec<uint32_t, 2>&
    );
    template void graphics_submit_context::set_constant<uint64_t, 2>(
        const shader_parameter_id&, const math::vec<uint64_t, 2>&
    );
    template void graphics_submit_context::set_constant<float, 2>(
        const shader_parameter_id&, const math::vec<float, 2>&
    );
    template void graphics_submit_context::set_constant<double, 2>(
        const shader_parameter_id&, const math::vec<double, 2>&
    );

    template void graphics_submit_context::set_constant<bool, 3>(const shader_parameter_id&, const math::vec<bool, 3>&);
    template void graphics_submit_context::set_constant<int32_t, 3>(
        const shader_parameter_id&, const math::vec<int32_t, 3>&
    );
    template void graphics_submit_context::set_constant<int64_t, 3>(
        const shader_parameter_id&, const math::vec<int64_t, 3>&
    );
    template void graphics_submit_context::set_constant<uint32_t, 3>(
        const shader_parameter_id&, const math::vec<uint32_t, 3>&
    );
    template void graphics_submit_context::set_constant<uint64_t, 3>(
        const shader_parameter_id&, const math::vec<uint64_t, 3>&
    );
    template void graphics_submit_context::set_constant<float, 3>(
        const shader_parameter_id&, const math::vec<float, 3>&
    );
    template void graphics_submit_context::set_constant<double, 3>(
        const shader_parameter_id&, const math::vec<double, 3>&
    );

    template void graphics_submit_context::set_constant<bool, 4>(const shader_parameter_id&, const math::vec<bool, 4>&);
    template void graphics_submit_context::set_constant<int32_t, 4>(
        const shader_parameter_id&, const math::vec<int32_t, 4>&
    );
    template void graphics_submit_context::set_constant<int64_t, 4>(
        const shader_parameter_id&, const math::vec<int64_t, 4>&
    );
    template void graphics_submit_context::set_constant<uint32_t, 4>(
        const shader_parameter_id&, const math::vec<uint32_t, 4>&
    );
    template void graphics_submit_context::set_constant<uint64_t, 4>(
        const shader_parameter_id&, const math::vec<uint64_t, 4>&
    );
    template void graphics_submit_context::set_constant<float, 4>(
        const shader_parameter_id&, const math::vec<float, 4>&
    );
    template void graphics_submit_context::set_constant<double, 4>(
        const shader_parameter_id&, const math::vec<double, 4>&
    );

    // Now imagine if there was a copy_submit_context

} // namespace veer::display::render