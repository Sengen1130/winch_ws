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

class Record {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.curTime = null;
      this.curLen = null;
      this.curDesLen = null;
    }
    else {
      if (initObj.hasOwnProperty('curTime')) {
        this.curTime = initObj.curTime
      }
      else {
        this.curTime = 0.0;
      }
      if (initObj.hasOwnProperty('curLen')) {
        this.curLen = initObj.curLen
      }
      else {
        this.curLen = 0.0;
      }
      if (initObj.hasOwnProperty('curDesLen')) {
        this.curDesLen = initObj.curDesLen
      }
      else {
        this.curDesLen = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Record
    // Serialize message field [curTime]
    bufferOffset = _serializer.float64(obj.curTime, buffer, bufferOffset);
    // Serialize message field [curLen]
    bufferOffset = _serializer.float64(obj.curLen, buffer, bufferOffset);
    // Serialize message field [curDesLen]
    bufferOffset = _serializer.float64(obj.curDesLen, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Record
    let len;
    let data = new Record(null);
    // Deserialize message field [curTime]
    data.curTime = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [curLen]
    data.curLen = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [curDesLen]
    data.curDesLen = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'system_control/Record';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '735e1749b0f1796a905e67b9dfc3aa99';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 curTime
    float64 curLen
    float64 curDesLen
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Record(null);
    if (msg.curTime !== undefined) {
      resolved.curTime = msg.curTime;
    }
    else {
      resolved.curTime = 0.0
    }

    if (msg.curLen !== undefined) {
      resolved.curLen = msg.curLen;
    }
    else {
      resolved.curLen = 0.0
    }

    if (msg.curDesLen !== undefined) {
      resolved.curDesLen = msg.curDesLen;
    }
    else {
      resolved.curDesLen = 0.0
    }

    return resolved;
    }
};

module.exports = Record;
