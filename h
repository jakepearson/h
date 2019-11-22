#!/usr/bin/env bash
set +x

HX_PATH="$HOME/.hx"
mkdir -p "$HX_PATH"

case "$OSTYPE" in
  *arwin*)
    OS="darwin"
    ;;
  *in32* | *indows*)
    OS="windows"
    ;;
  *)
    OS="linux"
esac

function GET_HELM_VERSION() {
  VERSION=$1
  HELM_PATH=$HX_PATH/helm-$VERSION
  HELM_TAR="$HELM_PATH.tar.gz"

  curl -L -o "$HELM_TAR" "https://get.helm.sh/helm-$VERSION-$OS-amd64.tar.gz"
  tar --extract --file="$HELM_TAR" --strip=1 --directory="$HX_PATH" $OS-amd64/helm 
  mv "$HX_PATH/helm" "$HELM_PATH"
  rm "$HELM_TAR"
}

# Ensure we have at least 1 helm version
KNOWN_VERSION="v2.16.0"
LOCAL_HELM=$HX_PATH/helm-$KNOWN_VERSION
HELM_PATH=$(command -v helm)
if [ -n "$HELM_PATH" ]; then
  LOCAL_HELM=$HELM_PATH
elif [ ! -f "$LOCAL_HELM" ]; then
  GET_HELM_VERSION $KNOWN_VERSION
fi

TARGET_VERSION=$($LOCAL_HELM version --template '{{ .Server.SemVer }}')
echo "TARGET-$TARGET_VERSION"
TARGET="$HX_PATH/helm-$TARGET_VERSION"

if [ ! -f "$TARGET" ]; then
  GET_HELM_VERSION "$TARGET_VERSION"
fi

$TARGET "$@"