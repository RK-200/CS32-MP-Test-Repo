import random

CASES: int = 300
SEED: int = 10293120
INPUTS: list[str] = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k']

f = open('test.txt', 'w')
random.seed(SEED)

size: int = 0
for _ in range(CASES):
    c = random.choice(INPUTS)
    match c:
        case 'a' | 'b':
            size += 1
            f.write(f"{c}\n")
            f.write(f"{random.randint(-2**63, 2**63 - 1)}\n")
        case 'c' | 'd':
            if size > 0: size -= 1
            f.write(f"{c}\n")
        case 'e' | 'f':
            if size > 0: f.write(f"{c}\n")
        case 'i':
            if size > 0:
                f.write(f"{c}\n")
                f.write(f"{random.randint(0, size-1)}\n")
        case 'j':
            if size > 0:
                f.write(f"{c}\n")
                f.write(f"{random.randint(0, size-1)}\n")
                f.write(f"{random.randint(-2**63, 2**63 - 1)}\n")
        case 'g' | 'h' | 'k' | 'l':
            f.write(f"{c}\n")
        case _:
            break
f.write("n\n")
f.close()
            
    
    

