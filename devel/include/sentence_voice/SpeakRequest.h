// Generated by gencpp from file sentence_voice/SpeakRequest.msg
// DO NOT EDIT!


#ifndef SENTENCE_VOICE_MESSAGE_SPEAKREQUEST_H
#define SENTENCE_VOICE_MESSAGE_SPEAKREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace sentence_voice
{
template <class ContainerAllocator>
struct SpeakRequest_
{
  typedef SpeakRequest_<ContainerAllocator> Type;

  SpeakRequest_()
    : header()
    , sentence()  {
    }
  SpeakRequest_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , sentence(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _sentence_type;
  _sentence_type sentence;





  typedef boost::shared_ptr< ::sentence_voice::SpeakRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sentence_voice::SpeakRequest_<ContainerAllocator> const> ConstPtr;

}; // struct SpeakRequest_

typedef ::sentence_voice::SpeakRequest_<std::allocator<void> > SpeakRequest;

typedef boost::shared_ptr< ::sentence_voice::SpeakRequest > SpeakRequestPtr;
typedef boost::shared_ptr< ::sentence_voice::SpeakRequest const> SpeakRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::sentence_voice::SpeakRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::sentence_voice::SpeakRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::sentence_voice::SpeakRequest_<ContainerAllocator1> & lhs, const ::sentence_voice::SpeakRequest_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.sentence == rhs.sentence;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::sentence_voice::SpeakRequest_<ContainerAllocator1> & lhs, const ::sentence_voice::SpeakRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace sentence_voice

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::sentence_voice::SpeakRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sentence_voice::SpeakRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sentence_voice::SpeakRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sentence_voice::SpeakRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sentence_voice::SpeakRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sentence_voice::SpeakRequest_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::sentence_voice::SpeakRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9f221efc5f4b3bac7ce4af102b32308b";
  }

  static const char* value(const ::sentence_voice::SpeakRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9f221efc5f4b3bacULL;
  static const uint64_t static_value2 = 0x7ce4af102b32308bULL;
};

template<class ContainerAllocator>
struct DataType< ::sentence_voice::SpeakRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "sentence_voice/SpeakRequest";
  }

  static const char* value(const ::sentence_voice::SpeakRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::sentence_voice::SpeakRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# 发送的请求是要说的话\n"
"std_msgs/Header header\n"
"string sentence\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::sentence_voice::SpeakRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::sentence_voice::SpeakRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.sentence);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SpeakRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sentence_voice::SpeakRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::sentence_voice::SpeakRequest_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "sentence: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.sentence);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SENTENCE_VOICE_MESSAGE_SPEAKREQUEST_H
