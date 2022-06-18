// Auto-generated. Do not edit!

// (in-package listen.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class listen_results {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.results = null;
      this.index = null;
    }
    else {
      if (initObj.hasOwnProperty('results')) {
        this.results = initObj.results
      }
      else {
        this.results = '';
      }
      if (initObj.hasOwnProperty('index')) {
        this.index = initObj.index
      }
      else {
        this.index = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type listen_results
    // Serialize message field [results]
    bufferOffset = _serializer.string(obj.results, buffer, bufferOffset);
    // Serialize message field [index]
    bufferOffset = _serializer.int8(obj.index, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type listen_results
    let len;
    let data = new listen_results(null);
    // Deserialize message field [results]
    data.results = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [index]
    data.index = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.results.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'listen/listen_results';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd09b62352cfbcede3511b368beb620d8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string results
    int8 index
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new listen_results(null);
    if (msg.results !== undefined) {
      resolved.results = msg.results;
    }
    else {
      resolved.results = ''
    }

    if (msg.index !== undefined) {
      resolved.index = msg.index;
    }
    else {
      resolved.index = 0
    }

    return resolved;
    }
};

module.exports = listen_results;
