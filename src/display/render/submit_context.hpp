#pragma once

#include "submit_context.h"

namespace veer::display::render
{
    template <RenderDataType T>
    void submit_context::set_constant(const shader_parameter_id& _param_id, const T& _val)
    {
        VEER_LOG_ERROR("Not Implemented");
    }

    template <RenderDataType T, size_t ELEM_COUNT>
    void submit_context::set_constant(const shader_parameter_id& _param_id, const math::vec<T, ELEM_COUNT>& _val)
        requires veer::LessEqual<ELEM_COUNT, 4>
    {
        VEER_LOG_ERROR("Not Implemented");
    }
} // namespace veer::display::render