// Auto-generated. Do not edit!

// (in-package potentiometer.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SendTimeRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.second = null;
      this.nsecond = null;
    }
    else {
      if (initObj.hasOwnProperty('second')) {
        this.second = initObj.second
      }
      else {
        this.second = 0;
      }
      if (initObj.hasOwnProperty('nsecond')) {
        this.nsecond = initObj.nsecond
      }
      else {
        this.nsecond = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SendTimeRequest
    // Serialize message field [second]
    bufferOffset = _serializer.int32(obj.second, buffer, bufferOffset);
    // Serialize message field [nsecond]
    bufferOffset = _serializer.int32(obj.nsecond, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SendTimeRequest
    let len;
    let data = new SendTimeRequest(null);
    // Deserialize message field [second]
    data.second = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [nsecond]
    data.nsecond = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'potentiometer/SendTimeRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7d08210cce4a961455ab53234f5ab98a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 second
    int32 nsecond
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SendTimeRequest(null);
    if (msg.second !== undefined) {
      resolved.second = msg.second;
    }
    else {
      resolved.second = 0
    }

    if (msg.nsecond !== undefined) {
      resolved.nsecond = msg.nsecond;
    }
    else {
      resolved.nsecond = 0
    }

    return resolved;
    }
};

class SendTimeResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SendTimeResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SendTimeResponse
    let len;
    let data = new SendTimeResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'potentiometer/SendTimeResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '358e233cde0c8a8bcfea4ce193f8fc15';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool success
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SendTimeResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: SendTimeRequest,
  Response: SendTimeResponse,
  md5sum() { return '586a87d88cd92bac79b2ab245f6dd834'; },
  datatype() { return 'potentiometer/SendTime'; }
};
