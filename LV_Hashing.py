def hash_function(key, size):
    return hash(key) % size

def linear_probing_insert(table, key, value):
    index = hash_function(key, len(table))
    while table[index] is not None:
        index = (index + 1) % len(table)
    table[index] = (key, value)

def linear_probing_search(table, key):
    index = hash_function(key, len(table))
    while table[index] is not None:
        k, v = table[index]
        if k == key:
            return v
        index = (index + 1) % len(table)
    return None

def double_hashing_insert(table, key, value):
    index = hash_function(key, len(table))
    step = 1 + (hash(key) % (len(table) - 1))
    while table[index] is not None:
        index = (index + step) % len(table)
    table[index] = (key, value)

def double_hashing_search(table, key):
    index = hash_function(key, len(table))
    step = 1 + (hash(key) % (len(table) - 1))
    while table[index] is not None:
        k, v = table[index]
        if k == key:
            return v
        index = (index + step) % len(table)
    return None

def test_collision_handling(client_list):
    size = 100
    linear_probing_table = [None] * size
    double_hashing_table = [None] * size

    for name, telephone in client_list:
        linear_probing_insert(linear_probing_table, name, telephone)
        double_hashing_insert(double_hashing_table, name, telephone)

    # Test linear probing
    comparisons_linear_probing = 0
    for name, _ in client_list:
        comparisons_linear_probing += 1
        linear_probing_search(linear_probing_table, name)

    # Test double hashing
    comparisons_double_hashing = 0
    for name, _ in client_list:
        comparisons_double_hashing += 1
        double_hashing_search(double_hashing_table, name)

    return comparisons_linear_probing, comparisons_double_hashing

if __name__ == "__main__":
    clients = [
        ("John", "123-456-7890"),
        ("Alice", "234-567-8901"),
        ("Bob", "345-678-9012"),
        ("Mary", "456-789-0123"),
        ("David", "567-890-1234")
    ]

    comparisons_linear_probing, comparisons_double_hashing = test_collision_handling(clients)

    print("Linear Probing Comparisons:", comparisons_linear_probing)
    print("Double Hashing Comparisons:", comparisons_double_hashing)