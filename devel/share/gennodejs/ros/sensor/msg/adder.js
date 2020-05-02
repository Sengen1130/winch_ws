// Auto-generated. Do not edit!

// (in-package sensor.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class adder {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.angle1 = null;
      this.angle2 = null;
    }
    else {
      if (initObj.hasOwnProperty('angle1')) {
        this.angle1 = initObj.angle1
      }
      else {
        this.angle1 = 0;
      }
      if (initObj.hasOwnProperty('angle2')) {
        this.angle2 = initObj.angle2
      }
      else {
        this.angle2 = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type adder
    // Serialize message field [angle1]
    bufferOffset = _serializer.int16(obj.angle1, buffer, bufferOffset);
    // Serialize message field [angle2]
    bufferOffset = _serializer.int16(obj.angle2, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type adder
    let len;
    let data = new adder(null);
    // Deserialize message field [angle1]
    data.angle1 = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [angle2]
    data.angle2 = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'sensor/adder';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ac081811000950995a96c1d7019e5876';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 angle1
    int16 angle2
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new adder(null);
    if (msg.angle1 !== undefined) {
      resolved.angle1 = msg.angle1;
    }
    else {
      resolved.angle1 = 0
    }

    if (msg.angle2 !== undefined) {
      resolved.angle2 = msg.angle2;
    }
    else {
      resolved.angle2 = 0
    }

    return resolved;
    }
};

module.exports = adder;
