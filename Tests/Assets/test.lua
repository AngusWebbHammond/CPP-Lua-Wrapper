local Test = {}

function Test.test()
    print("Test Called")
end

function Test.delta(dt)
    print("Delta Called with time: ", dt)
end

return Test