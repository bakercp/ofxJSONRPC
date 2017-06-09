ofxJSONRPC
==========

## Description

Create a JSONRPC server application with openFrameworks.

## Features

![Screenshot](https://github.com/bakercp/ofxJSONRPC/raw/master/docs/screen.png)

[JSONRPC 2.0](http://www.jsonrpc.org/specification) Implementation using openFrameworks events, WebSockets, etc.

Easily communicate between the browser and an openFrameworks application with the well-documented JSONRPC 2.0 protocol.

Compatible with https://github.com/Textalk/jquery.jsonrpcclient.js on the client side.

See examples and documentation for more information.

## Getting Started

To get started, generate the example project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).

## Documentation

API documentation can be found here.

## Build Status

Linux, macOS [![Build Status](https://travis-ci.org/bakercp/ofxJSONRPC.svg?branch=master)](https://travis-ci.org/bakercp/ofxJSONRPC)

Visual Studio, MSYS [![Build status](https://ci.appveyor.com/api/projects/status/knek9qnt6ycl5ra9/branch/master?svg=true)](https://ci.appveyor.com/project/bakercp/ofxjsonrpc/branch/master)

## Compatibility

### Branches

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via tagged versions, but only `stable` and `master` branches are actively supported.

### Requirements
- https://github.com/bakercp/ofxHTTP
  - https://github.com/bakercp/ofxIO
  - https://github.com/bakercp/ofxMediaType
  - https://github.com/bakercp/ofxSSLManager
  - https://github.com/bakercp/ofxNetworkUtils
  - ofxPoco

## Versioning

This project uses [Semantic Versioning](http://semver.org/), although strict adherence will only come into effect at version 1.0.0.

## Licensing

See `LICENSE.md`.

## Contributing

Pull Requests are always welcome, so if you make any improvements please feel free to float them back upstream :)

1. Fork this repository.
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.
