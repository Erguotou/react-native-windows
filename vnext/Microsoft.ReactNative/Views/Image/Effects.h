// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#pragma once

#include <BorderEffect.g.h>
#include <GaussianBlurEffect.g.h>

#pragma warning(push)
#pragma warning(disable : 28285 28196 6387 6319 26812)

#include "Microsoft.UI.Composition.Effects_Impl.h"

namespace winrt::Microsoft::ReactNative::implementation {
//-----------------------------------------------------------------------------------------------------------------
class BorderEffect
    : public BorderEffectT<BorderEffect, winrt::Microsoft::UI::Composition::Effects::implementation::EffectBase> {
 public:
  DECLARE_D2D_GUID(CLSID_D2D1Border);
  DECLARE_SINGLE_SOURCE(Source);
  DECLARE_POD_PROPERTY(
      ExtendX,
      winrt::Microsoft::ReactNative::CanvasEdgeBehavior,
      winrt::Microsoft::ReactNative::CanvasEdgeBehavior::Clamp,
      true);
  DECLARE_POD_PROPERTY(
      ExtendY,
      winrt::Microsoft::ReactNative::CanvasEdgeBehavior,
      winrt::Microsoft::ReactNative::CanvasEdgeBehavior::Clamp,
      true);
  DECLARE_NAMED_PROPERTY_MAPPING(
      {L"ExtendX", D2D1_BORDER_PROP_EDGE_MODE_X, PropertyMapping::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT},
      {L"ExtendY", D2D1_BORDER_PROP_EDGE_MODE_Y, PropertyMapping::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT});

 public:
  IFACEMETHODIMP GetPropertyCount(_Out_ UINT *count) override {
    *count = 2;
    return S_OK;
  }

  IFACEMETHODIMP GetProperty(UINT index, _Outptr_ abi::IPropertyValue **value) override {
    return UsePropertyFactory(value, [=]() {
      switch (index) {
        case D2D1_BORDER_PROP_EDGE_MODE_X:
          return winrt::PropertyValue::CreateUInt32((UINT32)m_ExtendX);
        case D2D1_BORDER_PROP_EDGE_MODE_Y:
          return winrt::PropertyValue::CreateUInt32((UINT32)m_ExtendY);
        default:
          throw winrt::hresult_invalid_argument();
      }
    });
  }
};

//-----------------------------------------------------------------------------------------------------------------
class GaussianBlurEffect : public GaussianBlurEffectT<
                               GaussianBlurEffect,
                               winrt::Microsoft::UI::Composition::Effects::implementation::EffectBase> {
 public:
  DECLARE_D2D_GUID(CLSID_D2D1GaussianBlur);
  DECLARE_SINGLE_SOURCE(Source);
  DECLARE_POD_PROPERTY(BlurAmount, float, 3.0f, value >= 0.0f && value <= 250.0f);
  DECLARE_POD_PROPERTY(
      Optimization,
      winrt::Microsoft::ReactNative::EffectOptimization,
      winrt::Microsoft::ReactNative::EffectOptimization::Balanced,
      true);
  DECLARE_POD_PROPERTY(
      BorderMode,
      winrt::Microsoft::ReactNative::EffectBorderMode,
      winrt::Microsoft::ReactNative::EffectBorderMode::Soft,
      true);
  DECLARE_NAMED_PROPERTY_MAPPING(
      {L"BlurAmount",
       D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION,
       PropertyMapping::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT},
      {L"Optimization", D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, PropertyMapping::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT},
      {L"BorderMode", D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, PropertyMapping::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT});

 public:
  IFACEMETHODIMP GetPropertyCount(_Out_ UINT *count) override {
    *count = 3;
    return S_OK;
  }

  IFACEMETHODIMP GetProperty(UINT index, _Outptr_ abi::IPropertyValue **value) override {
    return UsePropertyFactory(value, [=]() {
      switch (index) {
        case D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION:
          return winrt::PropertyValue::CreateSingle(m_BlurAmount);
        case D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION:
          return winrt::PropertyValue::CreateUInt32((UINT32)m_Optimization);
        case D2D1_GAUSSIANBLUR_PROP_BORDER_MODE:
          return winrt::PropertyValue::CreateUInt32((UINT32)m_BorderMode);
        default:
          throw winrt::hresult_invalid_argument();
      }
    });
  }
};

//-----------------------------------------------------------------------------------------------------------------

} // namespace winrt::Microsoft::ReactNative::implementation

#pragma warning(pop)
