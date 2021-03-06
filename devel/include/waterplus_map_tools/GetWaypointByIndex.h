// Generated by gencpp from file waterplus_map_tools/GetWaypointByIndex.msg
// DO NOT EDIT!


#ifndef WATERPLUS_MAP_TOOLS_MESSAGE_GETWAYPOINTBYINDEX_H
#define WATERPLUS_MAP_TOOLS_MESSAGE_GETWAYPOINTBYINDEX_H

#include <ros/service_traits.h>


#include <waterplus_map_tools/GetWaypointByIndexRequest.h>
#include <waterplus_map_tools/GetWaypointByIndexResponse.h>


namespace waterplus_map_tools
{

struct GetWaypointByIndex
{

typedef GetWaypointByIndexRequest Request;
typedef GetWaypointByIndexResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct GetWaypointByIndex
} // namespace waterplus_map_tools


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::waterplus_map_tools::GetWaypointByIndex > {
  static const char* value()
  {
    return "3d6fa8d914cdbd6f782b3a98c909799f";
  }

  static const char* value(const ::waterplus_map_tools::GetWaypointByIndex&) { return value(); }
};

template<>
struct DataType< ::waterplus_map_tools::GetWaypointByIndex > {
  static const char* value()
  {
    return "waterplus_map_tools/GetWaypointByIndex";
  }

  static const char* value(const ::waterplus_map_tools::GetWaypointByIndex&) { return value(); }
};


// service_traits::MD5Sum< ::waterplus_map_tools::GetWaypointByIndexRequest> should match
// service_traits::MD5Sum< ::waterplus_map_tools::GetWaypointByIndex >
template<>
struct MD5Sum< ::waterplus_map_tools::GetWaypointByIndexRequest>
{
  static const char* value()
  {
    return MD5Sum< ::waterplus_map_tools::GetWaypointByIndex >::value();
  }
  static const char* value(const ::waterplus_map_tools::GetWaypointByIndexRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::waterplus_map_tools::GetWaypointByIndexRequest> should match
// service_traits::DataType< ::waterplus_map_tools::GetWaypointByIndex >
template<>
struct DataType< ::waterplus_map_tools::GetWaypointByIndexRequest>
{
  static const char* value()
  {
    return DataType< ::waterplus_map_tools::GetWaypointByIndex >::value();
  }
  static const char* value(const ::waterplus_map_tools::GetWaypointByIndexRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::waterplus_map_tools::GetWaypointByIndexResponse> should match
// service_traits::MD5Sum< ::waterplus_map_tools::GetWaypointByIndex >
template<>
struct MD5Sum< ::waterplus_map_tools::GetWaypointByIndexResponse>
{
  static const char* value()
  {
    return MD5Sum< ::waterplus_map_tools::GetWaypointByIndex >::value();
  }
  static const char* value(const ::waterplus_map_tools::GetWaypointByIndexResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::waterplus_map_tools::GetWaypointByIndexResponse> should match
// service_traits::DataType< ::waterplus_map_tools::GetWaypointByIndex >
template<>
struct DataType< ::waterplus_map_tools::GetWaypointByIndexResponse>
{
  static const char* value()
  {
    return DataType< ::waterplus_map_tools::GetWaypointByIndex >::value();
  }
  static const char* value(const ::waterplus_map_tools::GetWaypointByIndexResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // WATERPLUS_MAP_TOOLS_MESSAGE_GETWAYPOINTBYINDEX_H
