//
// Created by jsumihiro on 10/11/22.
//

#ifndef RAIIENGINE_TYPES_HPP
#define RAIIENGINE_TYPES_HPP

#include <map>

namespace Forge
{
  enum ForgeType
  {
    Undefined,
    I32S,
    I32SVec2,
    I32SVec3,
    I32U,
    I32UVec2,
    I32UVec3,
    I64S,
    I64SVec2,
    I64SVec3,
    I64U,
    I64UVec2,
    I64UVec3,
    F32S,
    F32SVec2,
    F32SVec3,
    F64S,
    F64SVec2,
    F64SVec3,
 

  };
  
  
  ForgeType ForgeTypeFromPrimitiveAndDimensions(ForgeType baseType, unsigned numRows, unsigned numCols = 0)
  {
      return (ForgeType)(baseType + numRows);
  }
}




#endif //RAIIENGINE_TYPES_HPP
