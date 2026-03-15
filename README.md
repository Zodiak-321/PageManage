# PageManage

PageManage是一个可以管理页面的库,主要应用对象是LCD

---

- 支持创建删除页面,通过创建时的string名称来控制页面运行
- 页面相互独立,管理安全方便
- 通过map键值对查询,效率高
- 通过注册回调函数来实现不同页面的输入输出
- 拥有智能输出,可以区分固定页面和动态页面,节省单片机资源
  
---

## components

components库是PageManage库的一个拓展

目前有button,trigger,encoder,joystick这四种组件,用户也可以创建自己的独有组件

每一个组件都可以作为一个page输出,也可以单独创建输出

![](https://github.com/Zodiak-321/PageManage/blob/main/photos/aa5b506c199d846f44db91671ea4fe3c_720.jpg)

