// Generated by gencpp from file system_control/adder.msg
// DO NOT EDIT!


#ifndef SYSTEM_CONTROL_MESSAGE_ADDER_H
#define SYSTEM_CONTROL_MESSAGE_ADDER_H


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
struct adder_
{
  typedef adder_<ContainerAllocator> Type;

  adder_()
    : angle1(0)
    , angle2(0)  {
    }
  adder_(const ContainerAllocator& _alloc)
    : angle1(0)
    , angle2(0)  {
  (void)_alloc;
    }



   typedef int16_t _angle1_type;
  _angle1_type angle1;

   typedef int16_t _angle2_type;
  _angle2_type angle2;





  typedef boost::shared_ptr< ::system_control::adder_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::system_control::adder_<ContainerAllocator> const> ConstPtr;

}; // struct adder_

typedef ::system_control::adder_<std::allocator<void> > adder;

typedef boost::shared_ptr< ::system_control::adder > adderPtr;
typedef boost::shared_ptr< ::system_control::adder const> adderConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::system_control::adder_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::system_control::adder_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::system_control::adder_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::system_control::adder_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::system_control::adder_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::system_control::adder_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::system_control::adder_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::system_control::adder_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::system_control::adder_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ac081811000950995a96c1d7019e5876";
  }

  static const char* value(const ::system_control::adder_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xac08181100095099ULL;
  static const uint64_t static_value2 = 0x5a96c1d7019e5876ULL;
};

template<class ContainerAllocator>
struct DataType< ::system_control::adder_<ContainerAllocator> >
{
  static const char* value()
  {
    return "system_control/adder";
  }

  static const char* value(const ::system_control::adder_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::system_control::adder_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int16 angle1\n\
int16 angle2\n\
";
  }

  static const char* value(const ::system_control::adder_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::system_control::adder_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.angle1);
      stream.next(m.angle2);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct adder_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::system_control::adder_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::system_control::adder_<ContainerAllocator>& v)
  {
    s << indent << "angle1: ";
    Printer<int16_t>::stream(s, indent + "  ", v.angle1);
    s << indent << "angle2: ";
    Printer<int16_t>::stream(s, indent + "  ", v.angle2);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SYSTEM_CONTROL_MESSAGE_ADDER_H
