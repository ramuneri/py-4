import geometry

# Create Triangle objects and test them
triangle1 = geometry.Triangle(3, 4, 5)
print(f"Area: {triangle1.area()}")  # Expected Output: 6.0
print(f"Perimeter: {triangle1.perimeter()}")  # Expected Output: 12.0
print("-----------------------------")

triangle2 = geometry.Triangle(5, 5, 5)
print(f"Area: {triangle2.area()}")  # Expected Output: 10.8253175
print(f"Perimeter: {triangle2.perimeter()}")  # Expected Output: 15.0
print("-----------------------------")

triangle3 = geometry.Triangle(8, 8, 5)
print(f"Area: {triangle3.area()}")  # Expected Output: 15.0
print(f"Perimeter: {triangle3.perimeter()}")  # Expected Output: 21.0
print("-----------------------------")
