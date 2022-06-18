// Generated by gencpp from file waterplus_map_tools/GetChargerByNameRequest.msg
// DO NOT EDIT!


#ifndef WATERPLUS_MAP_TOOLS_MESSAGE_GETCHARGERBYNAMEREQUEST_H
#define WATERPLUS_MAP_TOOLS_MESSAGE_GETCHARGERBYNAMEREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace waterplus_map_tools
{
template <class ContainerAllocator>
struct GetChargerByNameRequest_
{
  typedef GetChargerByNameRequest_<ContainerAllocator> Type;

  GetChargerByNameRequest_()
    : name()  {
    }
  GetChargerByNameRequest_(const ContainerAllocator& _alloc)
    : name(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _name_type;
  _name_type name;





  typedef boost::shared_ptr< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> const> ConstPtr;

}; // struct GetChargerByNameRequest_

typedef ::waterplus_map_tools::GetChargerByNameRequest_<std::allocator<void> > GetChargerByNameRequest;

typedef boost::shared_ptr< ::waterplus_map_tools::GetChargerByNameRequest > GetChargerByNameRequestPtr;
typedef boost::shared_ptr< ::waterplus_map_tools::GetChargerByNameRequest const> GetChargerByNameRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator1> & lhs, const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator2> & rhs)
{
  return lhs.name == rhs.name;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator1> & lhs, const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace waterplus_map_tools

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c1f3d28f1b044c871e6eff2e9fc3c667";
  }

  static const char* value(const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc1f3d28f1b044c87ULL;
  static const uint64_t static_value2 = 0x1e6eff2e9fc3c667ULL;
};

template<class ContainerAllocator>
struct DataType< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "waterplus_map_tools/GetChargerByNameRequest";
  }

  static const char* value(const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string name\n"
;
  }

  static const char* value(const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.name);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetChargerByNameRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::waterplus_map_tools::GetChargerByNameRequest_<ContainerAllocator>& v)
  {
    s << indent << "name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name);
  }
};

} // namespace message_operations
} // namespace ros

#endif // WATERPLUS_MAP_TOOLS_MESSAGE_GETCHARGERBYNAMEREQUEST_H