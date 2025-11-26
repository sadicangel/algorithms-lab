const std = @import("std");

const LinkedListError = error{OutOfBounds, ConcurrentModification};

pub fn LinkedList(comptime T: type) type {
    return struct {
        allocator: std.mem.Allocator,
        head: ?*Node,

        const Self = @This();
        const Node = struct {
            value: T,
            next: ?*Node,
        };
        var _version: usize = 0;

        pub fn init(allocator: std.mem.Allocator) Self {
            return .{ .allocator = allocator, .head = null };
        }

        pub fn deinit(self: *Self) void {
            var maybe = self.head;
            while (maybe) |curr| {
                const next = curr.next;
                self.allocator.destroy(curr);
                maybe = next;
            }
        }

        pub fn version(self: *const Self) usize {
            _ = self;
            return _version;
        }

        pub fn append(self: *Self, value: T) !void {
            const node = try self.allocator.create(Node);
            node.* = .{ .value = value, .next = null };

            _version += 1;

            if (self.head == null) {
                self.head = node;
                return;
            }

            var curr = self.head.?;
            while (curr.next) |next| {
                curr = next;
            }
            curr.next = node;
        }

        pub fn prepend(self: *Self, value: T) !void {
            const node = try self.allocator.create(Node);
            node.* = .{ .value = value, .next = self.head };

            _version += 1;

            self.head = node;
        }

        pub fn insertAt(self: *Self, index: usize, value: T) !void {
            var prev: ?*Node = null;
            var curr: ?*Node = self.head;

            _version += 1;

            var i = index;
            while (i > 0) {
                prev = curr;
                curr = curr.?.next;
                i -= 1;
            }

            if (curr == null) {
                return LinkedListError.OutOfBounds;
            }

            const node = try self.allocator.create(Node);
            node.* = .{ .value = value, .next = curr };

            if (prev == null) {
                self.head = node;
            } else {
                prev.?.next = node;
            }
        }

        pub fn removeAt(self: *Self, index: usize) LinkedListError!void {
            var prev: ?*Node = null;
            var curr: ?*Node = self.head;

            _version += 1;

            var i = index;
            while (i > 0) {
                prev = curr;
                curr = curr.?.next;
                i -= 1;
            }

            if (curr == null) {
                return LinkedListError.OutOfBounds;
            }

            if (prev == null) {
                self.head = curr.?.next;
            } else {
                prev.?.next = curr.?.next;
            }
        }

        pub const Iterator = struct {
            list: *const Self,
            version: usize,
            current: ?*const Node,

            pub fn next(self: *Iterator) LinkedListError!?T {
                if(self.version != self.list.*.version()) {
                    return error.ConcurrentModification;
                }
                const node = self.current orelse return null;
                self.current = node.next;
                return node.value;
            }
        };

        pub fn iterator(self: *const Self) Iterator {
            return .{ .list = self, .version = _version, .current = self.head };
        }
    };
}
