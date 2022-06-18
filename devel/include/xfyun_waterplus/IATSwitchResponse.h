// Generated by gencpp from file xfyun_waterplus/IATSwitchResponse.msg
// DO NOT EDIT!


#ifndef XFYUN_WATERPLUS_MESSAGE_IATSWITCHRESPONSE_H
#define XFYUN_WATERPLUS_MESSAGE_IATSWITCHRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace xfyun_waterplus
{
template <class ContainerAllocator>
struct IATSwitchResponse_
{
  typedef IATSwitchResponse_<ContainerAllocator> Type;

  IATSwitchResponse_()
    {
    }
  IATSwitchResponse_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> const> ConstPtr;

}; // struct IATSwitchResponse_

typedef ::xfyun_waterplus::IATSwitchResponse_<std::allocator<void> > IATSwitchResponse;

typedef boost::shared_ptr< ::xfyun_waterplus::IATSwitchResponse > IATSwitchResponsePtr;
typedef boost::shared_ptr< ::xfyun_waterplus::IATSwitchResponse const> IATSwitchResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace xfyun_waterplus

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "xfyun_waterplus/IATSwitchResponse";
  }

  static const char* value(const ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct IATSwitchResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::xfyun_waterplus::IATSwitchResponse_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // XFYUN_WATERPLUS_MESSAGE_IATSWITCHRESPONSE_H