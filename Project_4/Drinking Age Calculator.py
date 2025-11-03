birthYear=int(input("Enter the year you were born: "))
currentYear=int(2025)
age=currentYear - birthYear
if age>=21:
    print("You are old enough to drink alcohol in the US.")
else:
    print("You are not old enough to drink alcohol in the US.")