// Generated by gencpp from file system_control/Timing.msg
// DO NOT EDIT!


#ifndef SYSTEM_CONTROL_MESSAGE_TIMING_H
#define SYSTEM_CONTROL_MESSAGE_TIMING_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace system_control
{
template <class ContainerAllocator>
struct Timing_
{
  typedef Timing_<ContainerAllocator> Type;

  Timing_()
    : start_time(0.0)
    , finish_time(0.0)  {
    }
  Timing_(const ContainerAllocator& _alloc)
    : start_time(0.0)
    , finish_time(0.0)  {
  (void)_alloc;
    }



   typedef double _start_time_type;
  _start_time_type start_time;

   typedef double _finish_time_type;
  _finish_time_type finish_time;





  typedef boost::shared_ptr< ::system_control::Timing_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::system_control::Timing_<ContainerAllocator> const> ConstPtr;

}; // struct Timing_

typedef ::system_control::Timing_<std::allocator<void> > Timing;

typedef boost::shared_ptr< ::system_control::Timing > TimingPtr;
typedef boost::shared_ptr< ::system_control::Timing const> TimingConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::system_control::Timing_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::system_control::Timing_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace system_control

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'system_control': ['/home/pi/winch_ws/src/system_control/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::system_control::Timing_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::system_control::Timing_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::system_control::Timing_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::system_control::Timing_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::system_control::Timing_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::system_control::Timing_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::system_control::Timing_<ContainerAllocator> >
{
  static const char* value()
  {
    return "77c54173386f0b1fc790cabaf77fbe5d";
  }

  static const char* value(const ::system_control::Timing_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x77c54173386f0b1fULL;
  static const uint64_t static_value2 = 0xc790cabaf77fbe5dULL;
};

template<class ContainerAllocator>
struct DataType< ::system_control::Timing_<ContainerAllocator> >
{
  static const char* value()
  {
    return "system_control/Timing";
  }

  static const char* value(const ::system_control::Timing_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::system_control::Timing_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 start_time\n\
float64 finish_time\n\
";
  }

  static const char* value(const ::system_control::Timing_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::system_control::Timing_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.start_time);
      stream.next(m.finish_time);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Timing_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::system_control::Timing_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::system_control::Timing_<ContainerAllocator>& v)
  {
    s << indent << "start_time: ";
    Printer<double>::stream(s, indent + "  ", v.start_time);
    s << indent << "finish_time: ";
    Printer<double>::stream(s, indent + "  ", v.finish_time);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SYSTEM_CONTROL_MESSAGE_TIMING_H