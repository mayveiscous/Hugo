local hugo = require("hugo")

hugo.init(800, 600, "Hugo Mesh Test")


local mesh = hugo.createMesh({
    -0.5, -0.5, 0.5,
     0.5, -0.5, 0.5,
     0.0,  0.5, 0.5
})

while not hugo.shouldClose() do
    hugo.pollEvents()

    hugo.beginFrame()

    hugo.drawMesh(mesh, 0, 0, 0)

    hugo.endFrame()
end