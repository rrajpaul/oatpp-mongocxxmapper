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


#ifndef oatpp_parser_mongocxx_mapping_Deserializer_hpp
#define oatpp_parser_mongocxx_mapping_Deserializer_hpp

#include "oatpp/core/data/mapping/type/List.hpp"
#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/data/mapping/type/Primitive.hpp"
#include "oatpp/core/data/mapping/type/Type.hpp"

#include "oatpp/core/collection/LinkedList.hpp"
#include "oatpp/core/Types.hpp"

#include <bsoncxx/builder/basic/document.hpp>

namespace oatpp { namespace parser { namespace mongocxx { namespace mapping {

/**
 * Json deserializer.
 * Deserializes json to oatpp DTO object. See [Data Transfer Object(DTO) component](https://oatpp.io/docs/components/dto/).
 */
class MongoToDto {
public:
  typedef oatpp::data::mapping::type::Type Type;
  
  typedef oatpp::data::mapping::type::AbstractObjectWrapper AbstractObjectWrapper;
  typedef oatpp::data::mapping::type::Object Object;
  
private:
  typedef oatpp::data::mapping::type::String String;
  typedef oatpp::data::mapping::type::Int32 Int32;
  typedef oatpp::data::mapping::type::Int64 Int64;
  typedef oatpp::data::mapping::type::Float32 Float32;
  typedef oatpp::data::mapping::type::Float64 Float64;
  typedef oatpp::data::mapping::type::Boolean Boolean;
  
  typedef oatpp::data::mapping::type::List<AbstractObjectWrapper> AbstractList;
  typedef oatpp::data::mapping::type::ListMap<String, AbstractObjectWrapper> AbstractListMap;
  
public:

  /**
   * Deserializer config.
   */
  class Config : public oatpp::base::Countable {
  public:
    /**
     * Constructor.
     */
    Config() = default;
  public:

    /**
     * Create shared Config.
     * @return - `std::shared_ptr` to Config.
     */
    static std::shared_ptr<Config> createShared(){
      return std::make_shared<Config>();
    }

    /**
     * Do not fail if unknown field is found in json.
     * "unknown field" is the one which is not present in DTO object class.
     */
    bool allowUnknownFields = true;
    
  };

public:

  /**
   * "'{' - expected"
   */
  static constexpr v_int32 ERROR_CODE_OBJECT_SCOPE_OPEN = 1;

  /**
   * "'}' - expected"
   */
  static constexpr v_int32 ERROR_CODE_OBJECT_SCOPE_CLOSE = 2;

  /**
   * "Unknown field"
   */
  static constexpr v_int32 ERROR_CODE_OBJECT_SCOPE_UNKNOWN_FIELD = 3;

  /**
   * "':' - expected"
   */
  static constexpr v_int32 ERROR_CODE_OBJECT_SCOPE_COLON_MISSING = 4;

  /**
   * "'[' - expected"
   */
  static constexpr v_int32 ERROR_CODE_ARRAY_SCOPE_OPEN = 5;

  /**
   * "']' - expected"
   */
  static constexpr v_int32 ERROR_CODE_ARRAY_SCOPE_CLOSE = 6;

  /**
   * "'true' or 'false' - expected"
   */
  static constexpr v_int32 ERROR_CODE_VALUE_BOOLEAN = 7;

private:
  
  
  static AbstractObjectWrapper readStringValue(const bsoncxx::types::value& caret);
  static AbstractObjectWrapper readInt8Value(const bsoncxx::types::value& caret);
  static AbstractObjectWrapper readInt16Value(const bsoncxx::types::value& caret);
  static AbstractObjectWrapper readInt32Value(const bsoncxx::types::value& caret);
  static AbstractObjectWrapper readInt64Value(const bsoncxx::types::value& caret);
  static AbstractObjectWrapper readFloat32Value(const bsoncxx::types::value& caret);
  static AbstractObjectWrapper readFloat64Value(const bsoncxx::types::value& caret);
  static AbstractObjectWrapper readBooleanValue(const bsoncxx::types::value& caret);
  static AbstractObjectWrapper readObjectValue(const Type* const type,
                                               const bsoncxx::types::value& caret,
                                               const std::shared_ptr<Config>& config);
  static AbstractObjectWrapper readListValue(const Type* const type,
                                             const bsoncxx::types::value& caret,
                                             const std::shared_ptr<Config>& config);
  
  static AbstractObjectWrapper readListMapValue(const Type* const type,
                                                const bsoncxx::types::value& caret,
                                                const std::shared_ptr<Config>& config);
  
  static AbstractObjectWrapper readValue(const Type* const type,
                                         const bsoncxx::types::value& caret,
                                         const std::shared_ptr<Config>& config);

//  static AbstractObjectWrapper readValue(const Type* const type,
//                                         const bsoncxx::array::element& caret,
//                                         const std::shared_ptr<Config>& config);
  
  static AbstractObjectWrapper readList(const Type* const type,
                                        const bsoncxx::types::value& caret,
                                        const std::shared_ptr<Config>& config);
  
  static AbstractObjectWrapper readListMap(const Type* const type,
                                           const bsoncxx::types::value& caret,
                                           const std::shared_ptr<Config>& config);
  
  static AbstractObjectWrapper readObject(const Type* const type,
                                          const bsoncxx::types::value& caret,
                                          const std::shared_ptr<Config>& config);

  static AbstractObjectWrapper readListMap(const Type* const type,
                                           const bsoncxx::document::view& caret,
                                           const std::shared_ptr<Config>& config);

  static AbstractObjectWrapper readObject(const Type* const type,
                                          const bsoncxx::document::view& caret,
                                          const std::shared_ptr<Config>& config);

public:

  /**
   * Deserialize json to oatpp DTO object.
   * @param caret - &id:bsoncxx::document::value;.
   * @param config - &l:Deserializer::Config;.
   * @param type - &id:oatpp::data::mapping::type::Type;.
   * @return - &id:oatpp::data::mapping::type::AbstractObjectWrapper; containing deserialized object.
   */
  static AbstractObjectWrapper deserialize(const bsoncxx::document::view& caret,
                                           const std::shared_ptr<Config>& config,
                                           const Type* const type) {

    if(type->classId.name == oatpp::data::mapping::type::__class::AbstractObject::CLASS_ID.name){
      return readObject(type, caret, config);
    } else if(type->classId.name == oatpp::data::mapping::type::__class::AbstractListMap::CLASS_ID.name){
      return readListMap(type, caret, config);
    }
    return AbstractObjectWrapper::empty();
  }
  
};
  
}}}}

#endif /* oatpp_parser_json_mapping_Deserializer_hpp */
