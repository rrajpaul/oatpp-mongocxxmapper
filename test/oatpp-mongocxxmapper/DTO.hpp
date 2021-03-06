/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *                         Benedikt-Alexander Mokroß <bam@icognize.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_test_web_app_DTOs_hpp
#define oatpp_test_web_app_DTOs_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace oatpp { namespace test { namespace mongocxxmapper {

#include OATPP_CODEGEN_BEGIN(DTO)

class SubDto : public oatpp::data::mapping::type::Object {
  DTO_INIT(SubDto, Object);
  DTO_FIELD(String, sub);
};

class TestDto : public oatpp::data::mapping::type::Object {

 DTO_INIT(TestDto, Object)

  DTO_FIELD(String, testValue);
  DTO_FIELD(String, nullValue);
  DTO_FIELD(Int8, i8Value);
  DTO_FIELD(Int16, i16Value);
  DTO_FIELD(Int32, i32Value);
  DTO_FIELD(Int64, i64Value);
  DTO_FIELD(Boolean, boolValue);
  DTO_FIELD(Fields<String>::ObjectWrapper, testMap);
  DTO_FIELD(List<String>::ObjectWrapper, testList);
  DTO_FIELD(List<Fields<String>::ObjectWrapper>::ObjectWrapper, testMapList);
  DTO_FIELD(Fields<Fields<String>::ObjectWrapper>::ObjectWrapper, testMapMap);
  DTO_FIELD(SubDto::ObjectWrapper, subObject);

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* oatpp_test_web_app_DTOs_hpp */
