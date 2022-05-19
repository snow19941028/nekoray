// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.27.1
// 	protoc        v3.20.1
// source: libcore.proto

package gen

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type TestMode int32

const (
	TestMode_TcpPing TestMode = 0
	TestMode_UrlTest TestMode = 1
)

// Enum value maps for TestMode.
var (
	TestMode_name = map[int32]string{
		0: "TcpPing",
		1: "UrlTest",
	}
	TestMode_value = map[string]int32{
		"TcpPing": 0,
		"UrlTest": 1,
	}
)

func (x TestMode) Enum() *TestMode {
	p := new(TestMode)
	*p = x
	return p
}

func (x TestMode) String() string {
	return protoimpl.X.EnumStringOf(x.Descriptor(), protoreflect.EnumNumber(x))
}

func (TestMode) Descriptor() protoreflect.EnumDescriptor {
	return file_libcore_proto_enumTypes[0].Descriptor()
}

func (TestMode) Type() protoreflect.EnumType {
	return &file_libcore_proto_enumTypes[0]
}

func (x TestMode) Number() protoreflect.EnumNumber {
	return protoreflect.EnumNumber(x)
}

// Deprecated: Use TestMode.Descriptor instead.
func (TestMode) EnumDescriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{0}
}

type EmptyReq struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields
}

func (x *EmptyReq) Reset() {
	*x = EmptyReq{}
	if protoimpl.UnsafeEnabled {
		mi := &file_libcore_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *EmptyReq) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*EmptyReq) ProtoMessage() {}

func (x *EmptyReq) ProtoReflect() protoreflect.Message {
	mi := &file_libcore_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use EmptyReq.ProtoReflect.Descriptor instead.
func (*EmptyReq) Descriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{0}
}

type EmptyResp struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields
}

func (x *EmptyResp) Reset() {
	*x = EmptyResp{}
	if protoimpl.UnsafeEnabled {
		mi := &file_libcore_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *EmptyResp) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*EmptyResp) ProtoMessage() {}

func (x *EmptyResp) ProtoReflect() protoreflect.Message {
	mi := &file_libcore_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use EmptyResp.ProtoReflect.Descriptor instead.
func (*EmptyResp) Descriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{1}
}

type ErrorResp struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Error string `protobuf:"bytes,1,opt,name=error,proto3" json:"error,omitempty"`
}

func (x *ErrorResp) Reset() {
	*x = ErrorResp{}
	if protoimpl.UnsafeEnabled {
		mi := &file_libcore_proto_msgTypes[2]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *ErrorResp) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*ErrorResp) ProtoMessage() {}

func (x *ErrorResp) ProtoReflect() protoreflect.Message {
	mi := &file_libcore_proto_msgTypes[2]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use ErrorResp.ProtoReflect.Descriptor instead.
func (*ErrorResp) Descriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{2}
}

func (x *ErrorResp) GetError() string {
	if x != nil {
		return x.Error
	}
	return ""
}

type LoadConfigReq struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	CoreConfig string `protobuf:"bytes,1,opt,name=coreConfig,proto3" json:"coreConfig,omitempty"`
}

func (x *LoadConfigReq) Reset() {
	*x = LoadConfigReq{}
	if protoimpl.UnsafeEnabled {
		mi := &file_libcore_proto_msgTypes[3]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *LoadConfigReq) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*LoadConfigReq) ProtoMessage() {}

func (x *LoadConfigReq) ProtoReflect() protoreflect.Message {
	mi := &file_libcore_proto_msgTypes[3]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use LoadConfigReq.ProtoReflect.Descriptor instead.
func (*LoadConfigReq) Descriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{3}
}

func (x *LoadConfigReq) GetCoreConfig() string {
	if x != nil {
		return x.CoreConfig
	}
	return ""
}

type TestReq struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Mode    TestMode `protobuf:"varint,1,opt,name=mode,proto3,enum=libcore.TestMode" json:"mode,omitempty"`
	Timeout int32    `protobuf:"varint,6,opt,name=timeout,proto3" json:"timeout,omitempty"`
	// TcpPing
	Address string `protobuf:"bytes,2,opt,name=address,proto3" json:"address,omitempty"`
	// UrlTest
	Config  *LoadConfigReq `protobuf:"bytes,3,opt,name=config,proto3" json:"config,omitempty"`
	Inbound string         `protobuf:"bytes,4,opt,name=inbound,proto3" json:"inbound,omitempty"`
	Url     string         `protobuf:"bytes,5,opt,name=url,proto3" json:"url,omitempty"`
}

func (x *TestReq) Reset() {
	*x = TestReq{}
	if protoimpl.UnsafeEnabled {
		mi := &file_libcore_proto_msgTypes[4]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *TestReq) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*TestReq) ProtoMessage() {}

func (x *TestReq) ProtoReflect() protoreflect.Message {
	mi := &file_libcore_proto_msgTypes[4]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use TestReq.ProtoReflect.Descriptor instead.
func (*TestReq) Descriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{4}
}

func (x *TestReq) GetMode() TestMode {
	if x != nil {
		return x.Mode
	}
	return TestMode_TcpPing
}

func (x *TestReq) GetTimeout() int32 {
	if x != nil {
		return x.Timeout
	}
	return 0
}

func (x *TestReq) GetAddress() string {
	if x != nil {
		return x.Address
	}
	return ""
}

func (x *TestReq) GetConfig() *LoadConfigReq {
	if x != nil {
		return x.Config
	}
	return nil
}

func (x *TestReq) GetInbound() string {
	if x != nil {
		return x.Inbound
	}
	return ""
}

func (x *TestReq) GetUrl() string {
	if x != nil {
		return x.Url
	}
	return ""
}

type TestResp struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Error string `protobuf:"bytes,1,opt,name=error,proto3" json:"error,omitempty"`
	Ms    int32  `protobuf:"varint,2,opt,name=ms,proto3" json:"ms,omitempty"`
}

func (x *TestResp) Reset() {
	*x = TestResp{}
	if protoimpl.UnsafeEnabled {
		mi := &file_libcore_proto_msgTypes[5]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *TestResp) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*TestResp) ProtoMessage() {}

func (x *TestResp) ProtoReflect() protoreflect.Message {
	mi := &file_libcore_proto_msgTypes[5]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use TestResp.ProtoReflect.Descriptor instead.
func (*TestResp) Descriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{5}
}

func (x *TestResp) GetError() string {
	if x != nil {
		return x.Error
	}
	return ""
}

func (x *TestResp) GetMs() int32 {
	if x != nil {
		return x.Ms
	}
	return 0
}

type QueryStatsReq struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Tag    string `protobuf:"bytes,1,opt,name=tag,proto3" json:"tag,omitempty"`
	Direct string `protobuf:"bytes,2,opt,name=direct,proto3" json:"direct,omitempty"`
}

func (x *QueryStatsReq) Reset() {
	*x = QueryStatsReq{}
	if protoimpl.UnsafeEnabled {
		mi := &file_libcore_proto_msgTypes[6]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *QueryStatsReq) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*QueryStatsReq) ProtoMessage() {}

func (x *QueryStatsReq) ProtoReflect() protoreflect.Message {
	mi := &file_libcore_proto_msgTypes[6]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use QueryStatsReq.ProtoReflect.Descriptor instead.
func (*QueryStatsReq) Descriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{6}
}

func (x *QueryStatsReq) GetTag() string {
	if x != nil {
		return x.Tag
	}
	return ""
}

func (x *QueryStatsReq) GetDirect() string {
	if x != nil {
		return x.Direct
	}
	return ""
}

type QueryStatsResp struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Traffic int64 `protobuf:"varint,1,opt,name=traffic,proto3" json:"traffic,omitempty"`
}

func (x *QueryStatsResp) Reset() {
	*x = QueryStatsResp{}
	if protoimpl.UnsafeEnabled {
		mi := &file_libcore_proto_msgTypes[7]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *QueryStatsResp) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*QueryStatsResp) ProtoMessage() {}

func (x *QueryStatsResp) ProtoReflect() protoreflect.Message {
	mi := &file_libcore_proto_msgTypes[7]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use QueryStatsResp.ProtoReflect.Descriptor instead.
func (*QueryStatsResp) Descriptor() ([]byte, []int) {
	return file_libcore_proto_rawDescGZIP(), []int{7}
}

func (x *QueryStatsResp) GetTraffic() int64 {
	if x != nil {
		return x.Traffic
	}
	return 0
}

var File_libcore_proto protoreflect.FileDescriptor

var file_libcore_proto_rawDesc = []byte{
	0x0a, 0x0d, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12,
	0x07, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x22, 0x0a, 0x0a, 0x08, 0x45, 0x6d, 0x70, 0x74,
	0x79, 0x52, 0x65, 0x71, 0x22, 0x0b, 0x0a, 0x09, 0x45, 0x6d, 0x70, 0x74, 0x79, 0x52, 0x65, 0x73,
	0x70, 0x22, 0x21, 0x0a, 0x09, 0x45, 0x72, 0x72, 0x6f, 0x72, 0x52, 0x65, 0x73, 0x70, 0x12, 0x14,
	0x0a, 0x05, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x05, 0x65,
	0x72, 0x72, 0x6f, 0x72, 0x22, 0x2f, 0x0a, 0x0d, 0x4c, 0x6f, 0x61, 0x64, 0x43, 0x6f, 0x6e, 0x66,
	0x69, 0x67, 0x52, 0x65, 0x71, 0x12, 0x1e, 0x0a, 0x0a, 0x63, 0x6f, 0x72, 0x65, 0x43, 0x6f, 0x6e,
	0x66, 0x69, 0x67, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x0a, 0x63, 0x6f, 0x72, 0x65, 0x43,
	0x6f, 0x6e, 0x66, 0x69, 0x67, 0x22, 0xc0, 0x01, 0x0a, 0x07, 0x54, 0x65, 0x73, 0x74, 0x52, 0x65,
	0x71, 0x12, 0x25, 0x0a, 0x04, 0x6d, 0x6f, 0x64, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x0e, 0x32,
	0x11, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x54, 0x65, 0x73, 0x74, 0x4d, 0x6f,
	0x64, 0x65, 0x52, 0x04, 0x6d, 0x6f, 0x64, 0x65, 0x12, 0x18, 0x0a, 0x07, 0x74, 0x69, 0x6d, 0x65,
	0x6f, 0x75, 0x74, 0x18, 0x06, 0x20, 0x01, 0x28, 0x05, 0x52, 0x07, 0x74, 0x69, 0x6d, 0x65, 0x6f,
	0x75, 0x74, 0x12, 0x18, 0x0a, 0x07, 0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x18, 0x02, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x07, 0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x12, 0x2e, 0x0a, 0x06,
	0x63, 0x6f, 0x6e, 0x66, 0x69, 0x67, 0x18, 0x03, 0x20, 0x01, 0x28, 0x0b, 0x32, 0x16, 0x2e, 0x6c,
	0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x4c, 0x6f, 0x61, 0x64, 0x43, 0x6f, 0x6e, 0x66, 0x69,
	0x67, 0x52, 0x65, 0x71, 0x52, 0x06, 0x63, 0x6f, 0x6e, 0x66, 0x69, 0x67, 0x12, 0x18, 0x0a, 0x07,
	0x69, 0x6e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x18, 0x04, 0x20, 0x01, 0x28, 0x09, 0x52, 0x07, 0x69,
	0x6e, 0x62, 0x6f, 0x75, 0x6e, 0x64, 0x12, 0x10, 0x0a, 0x03, 0x75, 0x72, 0x6c, 0x18, 0x05, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x03, 0x75, 0x72, 0x6c, 0x22, 0x30, 0x0a, 0x08, 0x54, 0x65, 0x73, 0x74,
	0x52, 0x65, 0x73, 0x70, 0x12, 0x14, 0x0a, 0x05, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x18, 0x01, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x05, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x12, 0x0e, 0x0a, 0x02, 0x6d, 0x73,
	0x18, 0x02, 0x20, 0x01, 0x28, 0x05, 0x52, 0x02, 0x6d, 0x73, 0x22, 0x39, 0x0a, 0x0d, 0x51, 0x75,
	0x65, 0x72, 0x79, 0x53, 0x74, 0x61, 0x74, 0x73, 0x52, 0x65, 0x71, 0x12, 0x10, 0x0a, 0x03, 0x74,
	0x61, 0x67, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x03, 0x74, 0x61, 0x67, 0x12, 0x16, 0x0a,
	0x06, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x06, 0x64,
	0x69, 0x72, 0x65, 0x63, 0x74, 0x22, 0x2a, 0x0a, 0x0e, 0x51, 0x75, 0x65, 0x72, 0x79, 0x53, 0x74,
	0x61, 0x74, 0x73, 0x52, 0x65, 0x73, 0x70, 0x12, 0x18, 0x0a, 0x07, 0x74, 0x72, 0x61, 0x66, 0x66,
	0x69, 0x63, 0x18, 0x01, 0x20, 0x01, 0x28, 0x03, 0x52, 0x07, 0x74, 0x72, 0x61, 0x66, 0x66, 0x69,
	0x63, 0x2a, 0x24, 0x0a, 0x08, 0x54, 0x65, 0x73, 0x74, 0x4d, 0x6f, 0x64, 0x65, 0x12, 0x0b, 0x0a,
	0x07, 0x54, 0x63, 0x70, 0x50, 0x69, 0x6e, 0x67, 0x10, 0x00, 0x12, 0x0b, 0x0a, 0x07, 0x55, 0x72,
	0x6c, 0x54, 0x65, 0x73, 0x74, 0x10, 0x01, 0x32, 0xcf, 0x02, 0x0a, 0x0e, 0x4c, 0x69, 0x62, 0x63,
	0x6f, 0x72, 0x65, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x12, 0x2f, 0x0a, 0x04, 0x45, 0x78,
	0x69, 0x74, 0x12, 0x11, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x45, 0x6d, 0x70,
	0x74, 0x79, 0x52, 0x65, 0x71, 0x1a, 0x12, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e,
	0x45, 0x6d, 0x70, 0x74, 0x79, 0x52, 0x65, 0x73, 0x70, 0x22, 0x00, 0x12, 0x34, 0x0a, 0x09, 0x4b,
	0x65, 0x65, 0x70, 0x41, 0x6c, 0x69, 0x76, 0x65, 0x12, 0x11, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f,
	0x72, 0x65, 0x2e, 0x45, 0x6d, 0x70, 0x74, 0x79, 0x52, 0x65, 0x71, 0x1a, 0x12, 0x2e, 0x6c, 0x69,
	0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x45, 0x6d, 0x70, 0x74, 0x79, 0x52, 0x65, 0x73, 0x70, 0x22,
	0x00, 0x12, 0x35, 0x0a, 0x05, 0x53, 0x74, 0x61, 0x72, 0x74, 0x12, 0x16, 0x2e, 0x6c, 0x69, 0x62,
	0x63, 0x6f, 0x72, 0x65, 0x2e, 0x4c, 0x6f, 0x61, 0x64, 0x43, 0x6f, 0x6e, 0x66, 0x69, 0x67, 0x52,
	0x65, 0x71, 0x1a, 0x12, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x45, 0x72, 0x72,
	0x6f, 0x72, 0x52, 0x65, 0x73, 0x70, 0x22, 0x00, 0x12, 0x2f, 0x0a, 0x04, 0x53, 0x74, 0x6f, 0x70,
	0x12, 0x11, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x45, 0x6d, 0x70, 0x74, 0x79,
	0x52, 0x65, 0x71, 0x1a, 0x12, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x45, 0x72,
	0x72, 0x6f, 0x72, 0x52, 0x65, 0x73, 0x70, 0x22, 0x00, 0x12, 0x2d, 0x0a, 0x04, 0x54, 0x65, 0x73,
	0x74, 0x12, 0x10, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x54, 0x65, 0x73, 0x74,
	0x52, 0x65, 0x71, 0x1a, 0x11, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x54, 0x65,
	0x73, 0x74, 0x52, 0x65, 0x73, 0x70, 0x22, 0x00, 0x12, 0x3f, 0x0a, 0x0a, 0x51, 0x75, 0x65, 0x72,
	0x79, 0x53, 0x74, 0x61, 0x74, 0x73, 0x12, 0x16, 0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65,
	0x2e, 0x51, 0x75, 0x65, 0x72, 0x79, 0x53, 0x74, 0x61, 0x74, 0x73, 0x52, 0x65, 0x71, 0x1a, 0x17,
	0x2e, 0x6c, 0x69, 0x62, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x51, 0x75, 0x65, 0x72, 0x79, 0x53, 0x74,
	0x61, 0x74, 0x73, 0x52, 0x65, 0x73, 0x70, 0x22, 0x00, 0x42, 0x12, 0x5a, 0x10, 0x6e, 0x65, 0x6b,
	0x6f, 0x72, 0x61, 0x79, 0x5f, 0x63, 0x6f, 0x72, 0x65, 0x2f, 0x67, 0x65, 0x6e, 0x62, 0x06, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_libcore_proto_rawDescOnce sync.Once
	file_libcore_proto_rawDescData = file_libcore_proto_rawDesc
)

func file_libcore_proto_rawDescGZIP() []byte {
	file_libcore_proto_rawDescOnce.Do(func() {
		file_libcore_proto_rawDescData = protoimpl.X.CompressGZIP(file_libcore_proto_rawDescData)
	})
	return file_libcore_proto_rawDescData
}

var file_libcore_proto_enumTypes = make([]protoimpl.EnumInfo, 1)
var file_libcore_proto_msgTypes = make([]protoimpl.MessageInfo, 8)
var file_libcore_proto_goTypes = []interface{}{
	(TestMode)(0),          // 0: libcore.TestMode
	(*EmptyReq)(nil),       // 1: libcore.EmptyReq
	(*EmptyResp)(nil),      // 2: libcore.EmptyResp
	(*ErrorResp)(nil),      // 3: libcore.ErrorResp
	(*LoadConfigReq)(nil),  // 4: libcore.LoadConfigReq
	(*TestReq)(nil),        // 5: libcore.TestReq
	(*TestResp)(nil),       // 6: libcore.TestResp
	(*QueryStatsReq)(nil),  // 7: libcore.QueryStatsReq
	(*QueryStatsResp)(nil), // 8: libcore.QueryStatsResp
}
var file_libcore_proto_depIdxs = []int32{
	0, // 0: libcore.TestReq.mode:type_name -> libcore.TestMode
	4, // 1: libcore.TestReq.config:type_name -> libcore.LoadConfigReq
	1, // 2: libcore.LibcoreService.Exit:input_type -> libcore.EmptyReq
	1, // 3: libcore.LibcoreService.KeepAlive:input_type -> libcore.EmptyReq
	4, // 4: libcore.LibcoreService.Start:input_type -> libcore.LoadConfigReq
	1, // 5: libcore.LibcoreService.Stop:input_type -> libcore.EmptyReq
	5, // 6: libcore.LibcoreService.Test:input_type -> libcore.TestReq
	7, // 7: libcore.LibcoreService.QueryStats:input_type -> libcore.QueryStatsReq
	2, // 8: libcore.LibcoreService.Exit:output_type -> libcore.EmptyResp
	2, // 9: libcore.LibcoreService.KeepAlive:output_type -> libcore.EmptyResp
	3, // 10: libcore.LibcoreService.Start:output_type -> libcore.ErrorResp
	3, // 11: libcore.LibcoreService.Stop:output_type -> libcore.ErrorResp
	6, // 12: libcore.LibcoreService.Test:output_type -> libcore.TestResp
	8, // 13: libcore.LibcoreService.QueryStats:output_type -> libcore.QueryStatsResp
	8, // [8:14] is the sub-list for method output_type
	2, // [2:8] is the sub-list for method input_type
	2, // [2:2] is the sub-list for extension type_name
	2, // [2:2] is the sub-list for extension extendee
	0, // [0:2] is the sub-list for field type_name
}

func init() { file_libcore_proto_init() }
func file_libcore_proto_init() {
	if File_libcore_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_libcore_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*EmptyReq); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_libcore_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*EmptyResp); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_libcore_proto_msgTypes[2].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*ErrorResp); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_libcore_proto_msgTypes[3].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*LoadConfigReq); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_libcore_proto_msgTypes[4].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*TestReq); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_libcore_proto_msgTypes[5].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*TestResp); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_libcore_proto_msgTypes[6].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*QueryStatsReq); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_libcore_proto_msgTypes[7].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*QueryStatsResp); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_libcore_proto_rawDesc,
			NumEnums:      1,
			NumMessages:   8,
			NumExtensions: 0,
			NumServices:   1,
		},
		GoTypes:           file_libcore_proto_goTypes,
		DependencyIndexes: file_libcore_proto_depIdxs,
		EnumInfos:         file_libcore_proto_enumTypes,
		MessageInfos:      file_libcore_proto_msgTypes,
	}.Build()
	File_libcore_proto = out.File
	file_libcore_proto_rawDesc = nil
	file_libcore_proto_goTypes = nil
	file_libcore_proto_depIdxs = nil
}
