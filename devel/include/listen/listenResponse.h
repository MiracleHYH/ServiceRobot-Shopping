// Generated by gencpp from file listen/listenResponse.msg
// DO NOT EDIT!


#ifndef LISTEN_MESSAGE_LISTENRESPONSE_H
#define LISTEN_MESSAGE_LISTENRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace listen
{
template <class ContainerAllocator>
struct listenResponse_
{
  typedef listenResponse_<ContainerAllocator> Type;

  listenResponse_()
    : result(false)  {
    }
  listenResponse_(const ContainerAllocator& _alloc)
    : result(false)  {
  (void)_alloc;
    }



   typedef uint8_t _result_type;
  _result_type result;





  typedef boost::shared_ptr< ::listen::listenResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::listen::listenResponse_<ContainerAllocator> const> ConstPtr;

}; // struct listenResponse_

typedef ::listen::listenResponse_<std::allocator<void> > listenResponse;

typedef boost::shared_ptr< ::listen::listenResponse > listenResponsePtr;
typedef boost::shared_ptr< ::listen::listenResponse const> listenResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::listen::listenResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::listen::listenResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::listen::listenResponse_<ContainerAllocator1> & lhs, const ::listen::listenResponse_<ContainerAllocator2> & rhs)
{
  return lhs.result == rhs.result;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::listen::listenResponse_<ContainerAllocator1> & lhs, const ::listen::listenResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace listen

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::listen::listenResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::listen::listenResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::listen::listenResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::listen::listenResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::listen::listenResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::listen::listenResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::listen::listenResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "eb13ac1f1354ccecb7941ee8fa2192e8";
  }

  static const char* value(const ::listen::listenResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xeb13ac1f1354ccecULL;
  static const uint64_t static_value2 = 0xb7941ee8fa2192e8ULL;
};

template<class ContainerAllocator>
struct DataType< ::listen::listenResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "listen/listenResponse";
  }

  static const char* value(const ::listen::listenResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::listen::listenResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool result\n"
;
  }

  static const char* value(const ::listen::listenResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::listen::listenResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.result);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct listenResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::listen::listenResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::listen::listenResponse_<ContainerAllocator>& v)
  {
    s << indent << "result: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.result);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LISTEN_MESSAGE_LISTENRESPONSE_H