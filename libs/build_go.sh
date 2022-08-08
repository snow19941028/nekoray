#!/bin/bash
set -e

source libs/deploy_common.sh
[ "$GOOS" == "windows" ] && [ "$GOARCH" == "amd64" ] && DEST=$DEPLOYMENT/windows64 || true
[ "$GOOS" == "linux" ] && [ "$GOARCH" == "amd64" ] && DEST=$DEPLOYMENT/linux64 || true
if [ -z $DEST ]; then
  echo "Please set GOOS GOARCH"
  exit
fi
rm -rf $DEST
mkdir -p $DEST

export CGO_ENABLED=0

#### Go: updater ####
pushd updater
go build -o $DEST -trimpath -ldflags "-w -s"
[ "$GOOS" == "linux" ] && mv $DEST/updater $DEST/launcher
popd

#### Go: nekoray_core ####
pushd ../v2ray-core
version_v2ray=$(git log --pretty=format:'%h' -n 1)
popd
pushd go
go build -v -o $DEST -trimpath -ldflags "-w -s -X main.version_v2ray=$version_v2ray -X main.version_standalone=$version_standalone"
popd

#### Windows only ####
if [ "$GOOS" != "windows" ]; then
  exit
fi

#### Go: sing-box ####
pushd $DEST
curl -Lso sing-box.zip https://github.com/SagerNet/sing-box/archive/64dbac813837bbadfaeec1a6e0d064875a123e5e.zip
unzip sing-box.zip
pushd sing-box-*/cmd/sing-box
go build -o $DEST -trimpath -ldflags "-w -s"
popd
rm -rf sing-box.zip sing-box-*
popd
