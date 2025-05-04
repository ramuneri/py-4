import fib

print(fib.fib(0)) # 0
print(fib.fib(1)) # 1
print(fib.fib(2)) # 1
print(fib.fib(3)) # 2
print(fib.fib(4)) # 3
print(fib.fib(5))  # 5
print(fib.fib(10)) # 55

try:
    print(fib.fib(-5))
except Exception as e:
    print(f"Error: {e}")  # "Fibonacci number cannot be negative."

try:
    print(fib.fib("hello"))
except Exception as e:
    print(f"Error: {e}")  #"Argument must be an integer."