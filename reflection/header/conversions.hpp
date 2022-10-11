//
// Created by jsumihiro on 10/10/22.
//

#ifndef RAIIENGINE_CONVERSIONS_HPP
#define RAIIENGINE_CONVERSIONS_HPP

#include "formats.hpp"
#include "types.hpp"
#include "spirv_cross/spirv.hpp"
#include "spirv_cross/spirv_common.hpp"

using spirv_cross::SPIRType;

constexpr Forge::Format SPVFormatToForge(spv::ImageFormat spvFormat)
{
  return Forge::Format::Undefined;
}

constexpr Forge::ForgeType SPVBaseTypeToForge(SPIRType::BaseType baseType)
{
    switch(baseType)
    {
      
      case SPIRType::BaseType::Int :
        return Forge::ForgeType::I32S;
      case SPIRType::BaseType::UInt :
        return Forge::ForgeType::I32U;
      case SPIRType::BaseType::Int64 :
        return Forge::ForgeType::I64S;
      case SPIRType::BaseType::UInt64 :
        return Forge::ForgeType::I64U;
      case SPIRType::BaseType::Float :
        return Forge::ForgeType::F32S;
      case SPIRType::BaseType::Double :
        return Forge::ForgeType::F64S;
      default:
        return Forge::ForgeType::Undefined;
    }
}

#endif //RAIIENGINE_CONVERSIONS_HPP
