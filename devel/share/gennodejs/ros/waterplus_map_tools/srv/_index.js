
"use strict";

let GetNumOfWaypoints = require('./GetNumOfWaypoints.js')
let GetWaypointByName = require('./GetWaypointByName.js')
let GetWaypointByIndex = require('./GetWaypointByIndex.js')
let SaveWaypoints = require('./SaveWaypoints.js')
let AddNewWaypoint = require('./AddNewWaypoint.js')
let GetChargerByName = require('./GetChargerByName.js')

module.exports = {
  GetNumOfWaypoints: GetNumOfWaypoints,
  GetWaypointByName: GetWaypointByName,
  GetWaypointByIndex: GetWaypointByIndex,
  SaveWaypoints: SaveWaypoints,
  AddNewWaypoint: AddNewWaypoint,
  GetChargerByName: GetChargerByName,
};
