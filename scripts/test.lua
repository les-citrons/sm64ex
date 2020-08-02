
function on_level_enter()
	print("level enter!")
end

function on_update()
	m = mario.get()
	m.forward_vel = 200;
	mario.set(m)
end

print("script loaded!")
