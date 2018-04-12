-- Function to execute
f1 = function()
for i=1,10 do
	print("ok1")
	thread.sleep(1)
end
end

f2 = function()
for i=1,10 do
	print("ok2")
	print(thread.status(th1))
	thread.sleep(1)
end
end

-- Start thread
th1 = thread.start(f1,512,7)
th2 = thread.start(f2,1024,3)
thread.list()