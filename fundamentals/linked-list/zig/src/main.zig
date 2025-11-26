const std = @import("std");
const LinkedList = @import("linked_list.zig").LinkedList;

pub fn main() !void {
    const allocator = std.heap.page_allocator;

    var list = LinkedList(u32).init(allocator);
    defer list.deinit();

    try list.append(10);
    try list.append(20);
    try list.append(30);

    try list.prepend(5);       // [5, 10, 20, 30]
    try list.insertAt(2, 15);  // [5, 10, 15, 20, 30]

    std.debug.print("List contents: ", .{});
    var it = list.iterator();
    while (try it.next()) |value| {
        std.debug.print("{d} ", .{value});
    }
    std.debug.print("\n", .{});

    try list.removeAt(2);      // remove 15

    std.debug.print("After removeAt(2): ", .{});
    var it2 = list.iterator();
    while (try it2.next()) |value| {
        std.debug.print("{d} ", .{value});
    }
    std.debug.print("\n", .{});

    // ---- Fail-fast iterator demo ----

    std.debug.print("Testing ConcurrentModification detection...\n", .{});

    var it3 = list.iterator();

    // First call should succeed
    const first_res = try it3.next();
    if (first_res) |first| {
        std.debug.print("First from it3: {d}\n", .{first});
    } else {
        std.debug.print("List was empty, cannot demo ConcurrentModification.\n", .{});
        return;
    }

    // Mutate the list after iterator was created
    try list.append(999);

    // Now call next() and inspect error vs value
    const second_res = it3.next() catch |err| {
        // Here err: LinkedListError
        switch (err) {
            error.ConcurrentModification => {
                std.debug.print("ConcurrentModification detected as expected.\n", .{});
                return;
            },
            error.OutOfBounds => {
                std.debug.print("Unexpected OutOfBounds from iterator.\n", .{});
                return;
            },
        }
    };

    // If we got here, there was no error: second_res is ?u32
    if (second_res) |value| {
        std.debug.print("Iterator did NOT fail fast, got value {d}\n", .{value});
    } else {
        std.debug.print("Iterator ended without detecting modification.\n", .{});
    }
}

