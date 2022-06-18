// Generated by gencpp from file xfyun_waterplus/IATSwitchRequest.msg
// DO NOT EDIT!


#ifndef XFYUN_WATERPLUS_MESSAGE_IATSWITCHREQUEST_H
#define XFYUN_WATERPLUS_MESSAGE_IATSWITCHREQUEST_H


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
struct IATSwitchRequest_
{
  typedef IATSwitchRequest_<ContainerAllocator> Type;

  IATSwitchRequest_()
    : active(false)
    , duration(0)  {
    }
  IATSwitchRequest_(const ContainerAllocator& _alloc)
    : active(false)
    , duration(0)  {
  (void)_alloc;
    }



   typedef uint8_t _active_type;
  _active_type active;

   typedef int32_t _duration_type;
  _duration_type duration;





  typedef boost::shared_ptr< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> const> ConstPtr;

}; // struct IATSwitchRequest_

typedef ::xfyun_waterplus::IATSwitchRequest_<std::allocator<void> > IATSwitchRequest;

typedef boost::shared_ptr< ::xfyun_waterplus::IATSwitchRequest > IATSwitchRequestPtr;
typedef boost::shared_ptr< ::xfyun_waterplus::IATSwitchRequest const> IATSwitchRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator1> & lhs, const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator2> & rhs)
{
  return lhs.active == rhs.active &&
    lhs.duration == rhs.duration;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator1> & lhs, const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace xfyun_waterplus

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d1f8595ffdb7d3156100a6358d5facc1";
  }

  static const char* value(const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd1f8595ffdb7d315ULL;
  static const uint64_t static_value2 = 0x6100a6358d5facc1ULL;
};

template<class ContainerAllocator>
struct DataType< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "xfyun_waterplus/IATSwitchRequest";
  }

  static const char* value(const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool active\n"
"int32 duration\n"
;
  }

  static const char* value(const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.active);
      stream.next(m.duration);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct IATSwitchRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::xfyun_waterplus::IATSwitchRequest_<ContainerAllocator>& v)
  {
    s << indent << "active: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.active);
    s << indent << "duration: ";
    Printer<int32_t>::stream(s, indent + "  ", v.duration);
  }
};

} // namespace message_operations
} // namespace ros

#endif // XFYUN_WATERPLUS_MESSAGE_IATSWITCHREQUEST_H
