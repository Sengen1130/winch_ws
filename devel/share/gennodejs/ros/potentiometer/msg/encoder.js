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

class encoder {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.desired = null;
      this.actual = null;
    }
    else {
      if (initObj.hasOwnProperty('desired')) {
        this.desired = initObj.desired
      }
      else {
        this.desired = 0;
      }
      if (initObj.hasOwnProperty('actual')) {
        this.actual = initObj.actual
      }
      else {
        this.actual = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type encoder
    // Serialize message field [desired]
    bufferOffset = _serializer.int32(obj.desired, buffer, bufferOffset);
    // Serialize message field [actual]
    bufferOffset = _serializer.int32(obj.actual, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type encoder
    let len;
    let data = new encoder(null);
    // Deserialize message field [desired]
    data.desired = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [actual]
    data.actual = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'potentiometer/encoder';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '228bf8fb168564ebccf3e320dc392525';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 desired
    int32 actual
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new encoder(null);
    if (msg.desired !== undefined) {
      resolved.desired = msg.desired;
    }
    else {
      resolved.desired = 0
    }

    if (msg.actual !== undefined) {
      resolved.actual = msg.actual;
    }
    else {
      resolved.actual = 0
    }

    return resolved;
    }
};

module.exports = encoder;
