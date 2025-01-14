#pragma once

#include <enoki/array.h>
#include <enoki/matrix.h>
#include <enoki/cuda.h>
#include <enoki/autodiff.h>

using namespace enoki;

namespace psdr
{

/********************************************
 * GPU array types
 ********************************************/

template <typename T, bool ad>
using Type      = typename std::conditional<ad,
                                            DiffArray<CUDAArray<T>>,
                                            CUDAArray<T>>::type;

// Scalar arrays (GPU)

template <bool ad>
using Float     = Type<float, ad>;

template <bool ad>
using Int       = Type<int32_t, ad>;

using FloatC    = Float<false>;
using FloatD    = Float<true>;

using IntC      = Int<false>;
using IntD      = Int<true>;

// Vector arrays (GPU)

template <int n, bool ad>
using Vectorf   = Array<Float<ad>, n>;

template <int n, bool ad>
using Vectori   = Array<Int<ad>, n>;

template <int n, bool ad>
using Matrixf   = Matrix<Float<ad>, n>;

template <bool ad>
using Vector2f  = Vectorf<2, ad>;

template <bool ad>
using Vector2i  = Vectori<2, ad>;

template <bool ad>
using Vector3f  = Vectorf<3, ad>;

template <bool ad>
using Vector3i  = Vectori<3, ad>;

template <bool ad>
using Vector4f  = Vectorf<4, ad>;

template <bool ad>
using Vector4i  = Vectori<4, ad>;

using Vector2fC = Vector2f<false>;
using Vector2fD = Vector2f<true>;

using Vector2iC = Vector2i<false>;
using Vector2iD = Vector2i<true>;

using Vector3fC = Vector3f<false>;
using Vector3fD = Vector3f<true>;

using Vector3iC = Vector3i<false>;
using Vector3iD = Vector3i<true>;

using Vector4fC = Vector4f<false>;
using Vector4fD = Vector4f<true>;

using Vector4iC = Vector4i<false>;
using Vector4iD = Vector4i<true>;

// Matrix arrays (GPU)

template <bool ad>
using Matrix3f  = Matrixf<3, ad>;

template <bool ad>
using Matrix4f  = Matrixf<4, ad>;

using Matrix3fC = Matrix3f<false>;
using Matrix3fD = Matrix3f<true>;

using Matrix4fC = Matrix4f<false>;
using Matrix4fD = Matrix4f<true>;

// Mask arrays (GPU)

template <bool ad>
using Mask      = mask_t<Float<ad>>;

using MaskC     = Mask<false>;
using MaskD     = Mask<true>;

// Spectrum types (GPU)

template <bool ad>
using Spectrum  = Vectorf<PSDR_NUM_CHANNELS, ad>;

using SpectrumC = Spectrum<false>;
using SpectrumD = Spectrum<true>;

/********************************************
 * CPU types
 ********************************************/

// Scalar types (CPU)

using ScalarVector2f = Array<float, 2>;
using ScalarVector3f = Array<float, 3>;
using ScalarVector4f = Array<float, 4>;

using ScalarVector2i = Array<int, 2>;
using ScalarVector3i = Array<int, 3>;
using ScalarVector4i = Array<int, 4>;

using ScalarMatrix2f = Matrix<float, 2>;
using ScalarMatrix3f = Matrix<float, 3>;
using ScalarMatrix4f = Matrix<float, 4>;

/********************************************
 * Triangle info types
 ********************************************/

template <typename Float_>
struct TriangleInfo_ {
    static constexpr bool ad = std::is_same_v<Float_, FloatD>;

    Vector3f<ad> p0, e1, e2, n0, n1, n2, face_normal;
    Float<ad>    face_area;
    Int<ad>      v0_idx, v1_idx, v2_idx;

    ENOKI_STRUCT(TriangleInfo_, p0, e1, e2,
                                n0, n1, n2,
                                face_normal,
                                face_area,
                                v0_idx, v1_idx, v2_idx)
};

template <bool ad>
using TriangleInfo  = TriangleInfo_<Float<ad>>;

using TriangleInfoC = TriangleInfo<false>;
using TriangleInfoD = TriangleInfo<true>;

template <bool ad>
using TriangleUV = Array<Vector2f<ad>, 3>;

using TriangleUVC   = TriangleUV<false>;
using TriangleUVD   = TriangleUV<true>;

/********************************************
 * Others
 ********************************************/

// For samplers

using UIntC     = Type<uint32_t, false>;
using UInt64C   = Type<uint64_t, false>;

// Render options

struct RenderOption {
    RenderOption() : width(128), height(128), spp(1), sppe(1), log_level(1) {}
    RenderOption(int w, int h, int s) : width(w), height(h), spp(s), sppe(s), sppse(s), log_level(1) {}
    RenderOption(int w, int h, int s1, int s2) : width(w), height(h), spp(s1), sppe(s2), sppse(s2), log_level(1) {}
    RenderOption(int w, int h, int s1, int s2, int s3) : width(w), height(h), spp(s1), sppe(s2), sppse(s3), log_level(1) {}

    int width, height;  // Image resolution
    int spp;            // Spp for the main image/interior integral
    int sppe;           // Spp for primary edge integral
    int sppse;          // Spp for secondary edge integral
    int log_level;
};

} // namespace psdr

ENOKI_STRUCT_SUPPORT(psdr::TriangleInfo_, p0, e1, e2, n0, n1, n2,
                                          face_normal, face_area,
                                          v0_idx, v1_idx, v2_idx)
