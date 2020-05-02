// Auto-generated. Do not edit!

// (in-package system_control.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Timing {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.start_time = null;
      this.finish_time = null;
    }
    else {
      if (initObj.hasOwnProperty('start_time')) {
        this.start_time = initObj.start_time
      }
      else {
        this.start_time = 0.0;
      }
      if (initObj.hasOwnProperty('finish_time')) {
        this.finish_time = initObj.finish_time
      }
      else {
        this.finish_time = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Timing
    // Serialize message field [start_time]
    bufferOffset = _serializer.float64(obj.start_time, buffer, bufferOffset);
    // Serialize message field [finish_time]
    bufferOffset = _serializer.float64(obj.finish_time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Timing
    let len;
    let data = new Timing(null);
    // Deserialize message field [start_time]
    data.start_time = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [finish_time]
    data.finish_time = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'system_control/Timing';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '77c54173386f0b1fc790cabaf77fbe5d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 start_time
    float64 finish_time
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Timing(null);
    if (msg.start_time !== undefined) {
      resolved.start_time = msg.start_time;
    }
    else {
      resolved.start_time = 0.0
    }

    if (msg.finish_time !== undefined) {
      resolved.finish_time = msg.finish_time;
    }
    else {
      resolved.finish_time = 0.0
    }

    return resolved;
    }
};

module.exports = Timing;
