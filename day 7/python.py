total = 0
area = []
while True:
    try:
        target, nums = input().split(':')
        target = int(target)
        nums = list(map(int, nums.split()))
        for b in range(3 ** (len(nums) - 1)):
            current = nums[0]
            for i, n in enumerate(nums[1:]):
                if b % 3 == 1:
                    current *= n
                elif b % 3 == 2:
                    current = int(str(current) + str(n))
                else:
                    current += n
                
                b = b // 3
                if target < current:
                    break
            if current == target:
                total += target
                break
        print(target, nums)

    except EOFError:
        break  # Exit loop on EOF

print(total)