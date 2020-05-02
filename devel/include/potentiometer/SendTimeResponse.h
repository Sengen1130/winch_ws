// Generated by gencpp from file potentiometer/SendTimeResponse.msg
// DO NOT EDIT!


#ifndef POTENTIOMETER_MESSAGE_SENDTIMERESPONSE_H
#define POTENTIOMETER_MESSAGE_SENDTIMERESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace potentiometer
{
template <class ContainerAllocator>
struct SendTimeResponse_
{
  typedef SendTimeResponse_<ContainerAllocator> Type;

  SendTimeResponse_()
    : success(false)  {
    }
  SendTimeResponse_(const ContainerAllocator& _alloc)
    : success(false)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;





  typedef boost::shared_ptr< ::potentiometer::SendTimeResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::potentiometer::SendTimeResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SendTimeResponse_

typedef ::potentiometer::SendTimeResponse_<std::allocator<void> > SendTimeResponse;

typedef boost::shared_ptr< ::potentiometer::SendTimeResponse > SendTimeResponsePtr;
typedef boost::shared_ptr< ::potentiometer::SendTimeResponse const> SendTimeResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::potentiometer::SendTimeResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::potentiometer::SendTimeResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace potentiometer

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'potentiometer': ['/home/pi/winch_ws/src/potentiometer/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::potentiometer::SendTimeResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::potentiometer::SendTimeResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::potentiometer::SendTimeResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::potentiometer::SendTimeResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::potentiometer::SendTimeResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::potentiometer::SendTimeResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::potentiometer::SendTimeResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "358e233cde0c8a8bcfea4ce193f8fc15";
  }

  static const char* value(const ::potentiometer::SendTimeResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x358e233cde0c8a8bULL;
  static const uint64_t static_value2 = 0xcfea4ce193f8fc15ULL;
};

template<class ContainerAllocator>
struct DataType< ::potentiometer::SendTimeResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "potentiometer/SendTimeResponse";
  }

  static const char* value(const ::potentiometer::SendTimeResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::potentiometer::SendTimeResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool success\n\
";
  }

  static const char* value(const ::potentiometer::SendTimeResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::potentiometer::SendTimeResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SendTimeResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::potentiometer::SendTimeResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::potentiometer::SendTimeResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
  }
};

} // namespace message_operations
} // namespace ros

#endif // POTENTIOMETER_MESSAGE_SENDTIMERESPONSE_H