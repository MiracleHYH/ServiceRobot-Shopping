// Generated by gencpp from file listen/listen_results.msg
// DO NOT EDIT!


#ifndef LISTEN_MESSAGE_LISTEN_RESULTS_H
#define LISTEN_MESSAGE_LISTEN_RESULTS_H


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
struct listen_results_
{
  typedef listen_results_<ContainerAllocator> Type;

  listen_results_()
    : results()
    , index(0)  {
    }
  listen_results_(const ContainerAllocator& _alloc)
    : results(_alloc)
    , index(0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _results_type;
  _results_type results;

   typedef int8_t _index_type;
  _index_type index;





  typedef boost::shared_ptr< ::listen::listen_results_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::listen::listen_results_<ContainerAllocator> const> ConstPtr;

}; // struct listen_results_

typedef ::listen::listen_results_<std::allocator<void> > listen_results;

typedef boost::shared_ptr< ::listen::listen_results > listen_resultsPtr;
typedef boost::shared_ptr< ::listen::listen_results const> listen_resultsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::listen::listen_results_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::listen::listen_results_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::listen::listen_results_<ContainerAllocator1> & lhs, const ::listen::listen_results_<ContainerAllocator2> & rhs)
{
  return lhs.results == rhs.results &&
    lhs.index == rhs.index;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::listen::listen_results_<ContainerAllocator1> & lhs, const ::listen::listen_results_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace listen

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::listen::listen_results_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::listen::listen_results_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::listen::listen_results_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::listen::listen_results_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::listen::listen_results_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::listen::listen_results_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::listen::listen_results_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d09b62352cfbcede3511b368beb620d8";
  }

  static const char* value(const ::listen::listen_results_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd09b62352cfbcedeULL;
  static const uint64_t static_value2 = 0x3511b368beb620d8ULL;
};

template<class ContainerAllocator>
struct DataType< ::listen::listen_results_<ContainerAllocator> >
{
  static const char* value()
  {
    return "listen/listen_results";
  }

  static const char* value(const ::listen::listen_results_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::listen::listen_results_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string results\n"
"int8 index\n"
;
  }

  static const char* value(const ::listen::listen_results_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::listen::listen_results_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.results);
      stream.next(m.index);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct listen_results_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::listen::listen_results_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::listen::listen_results_<ContainerAllocator>& v)
  {
    s << indent << "results: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.results);
    s << indent << "index: ";
    Printer<int8_t>::stream(s, indent + "  ", v.index);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LISTEN_MESSAGE_LISTEN_RESULTS_H
