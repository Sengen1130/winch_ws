// Auto-generated. Do not edit!

// (in-package potentiometer.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Log {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.data0 = null;
      this.data1 = null;
      this.data2 = null;
      this.data3 = null;
      this.data4 = null;
    }
    else {
      if (initObj.hasOwnProperty('data0')) {
        this.data0 = initObj.data0
      }
      else {
        this.data0 = 0.0;
      }
      if (initObj.hasOwnProperty('data1')) {
        this.data1 = initObj.data1
      }
      else {
        this.data1 = 0;
      }
      if (initObj.hasOwnProperty('data2')) {
        this.data2 = initObj.data2
      }
      else {
        this.data2 = 0;
      }
      if (initObj.hasOwnProperty('data3')) {
        this.data3 = initObj.data3
      }
      else {
        this.data3 = 0.0;
      }
      if (initObj.hasOwnProperty('data4')) {
        this.data4 = initObj.data4
      }
      else {
        this.data4 = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Log
    // Serialize message field [data0]
    bufferOffset = _serializer.float64(obj.data0, buffer, bufferOffset);
    // Serialize message field [data1]
    bufferOffset = _serializer.int32(obj.data1, buffer, bufferOffset);
    // Serialize message field [data2]
    bufferOffset = _serializer.int32(obj.data2, buffer, bufferOffset);
    // Serialize message field [data3]
    bufferOffset = _serializer.float64(obj.data3, buffer, bufferOffset);
    // Serialize message field [data4]
    bufferOffset = _serializer.float64(obj.data4, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Log
    let len;
    let data = new Log(null);
    // Deserialize message field [data0]
    data.data0 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [data1]
    data.data1 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [data2]
    data.data2 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [data3]
    data.data3 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [data4]
    data.data4 = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'potentiometer/Log';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3bc9c20a1bbcd292f1a59fbbe069fe8d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 data0
    int32 data1
    int32 data2
    float64 data3
    float64 data4
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Log(null);
    if (msg.data0 !== undefined) {
      resolved.data0 = msg.data0;
    }
    else {
      resolved.data0 = 0.0
    }

    if (msg.data1 !== undefined) {
      resolved.data1 = msg.data1;
    }
    else {
      resolved.data1 = 0
    }

    if (msg.data2 !== undefined) {
      resolved.data2 = msg.data2;
    }
    else {
      resolved.data2 = 0
    }

    if (msg.data3 !== undefined) {
      resolved.data3 = msg.data3;
    }
    else {
      resolved.data3 = 0.0
    }

    if (msg.data4 !== undefined) {
      resolved.data4 = msg.data4;
    }
    else {
      resolved.data4 = 0.0
    }

    return resolved;
    }
};

module.exports = Log;
