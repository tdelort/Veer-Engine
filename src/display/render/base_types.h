#pragma once

#include <core/math/vec.h>

namespace veer::display::render
{
    struct viewport
    {
        math::vec2u m_position{0u, 0u};
        math::vec2u m_size{0u, 0u};
        math::vec2f m_depth{0.f, 1.f};
    };

    struct rect
    {
        math::vec2u m_min{0u, 0u};
        math::vec2u m_max{0u, 0u};
    };

    static constexpr size_t s_max_viewport_and_scissors_count = 16u;
    static constexpr size_t s_max_color_render_targets = 8u;

    struct render_data_type_info
    {
        const std::type_info& m_cpu_typeid;
        size_t m_cpu_size;
        size_t m_gpu_size;
    };

#define FILL_CPU_INFO(_type) typeid(_type), sizeof(_type)

#if defined(D3D12_RENDER_BACKEND)
#define SELECT_GPU_SIZE(_dx12, _vk, _mtl) (_dx12)
#elif defined(VULKAN_RENDER_BACKEND)
#define SELECT_GPU_SIZE(_dx12, _vk, _mtl) (_vk)
#error Change 0 values in s_render_data_types
#elif defined(METAL_RENDER_BACKEND)
#define SELECT_GPU_SIZE(_dx12, _vk, _mtl) (_mtl)
#error Change 0 values in s_render_data_types
#endif

    // TODO : change 0 when implementing other backends
    static constexpr render_data_type_info s_render_data_types[] = {
        {FILL_CPU_INFO(bool),     SELECT_GPU_SIZE(4, 0, 0)},
        {FILL_CPU_INFO(int32_t),  SELECT_GPU_SIZE(4, 0, 0)},
        {FILL_CPU_INFO(int64_t),  SELECT_GPU_SIZE(8, 0, 0)},
        {FILL_CPU_INFO(uint32_t), SELECT_GPU_SIZE(4, 0, 0)},
        {FILL_CPU_INFO(uint64_t), SELECT_GPU_SIZE(8, 0, 0)},
        {FILL_CPU_INFO(float),    SELECT_GPU_SIZE(4, 0, 0)},
        {FILL_CPU_INFO(double),   SELECT_GPU_SIZE(8, 0, 0)},
    };

#undef SELECT_GPU_SIZE
#undef FILL_CPU_INFO
} // namespace veer::display::render