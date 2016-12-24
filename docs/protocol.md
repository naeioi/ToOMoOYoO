# 协议编码

## Controller <-> Controller
- Register
注册
```js
Signup\n
{
    username: "naeioi",
    password: "ToOMoOYoO"
}\0
```
- SignupRes
注册结果
```js
SignupRes\n
{
    /* code 
     * 0 成功
     * 1 密码太短
     * 2 密码太长
     * 3 用户名已存在
     * 4 未知错误
     */
    code: 0,
    /* session = MD5(string(rand()) + to_string(uid)) */
    session: "9e107d9d372bb6826bd81d3542a419d6",
    message: "额外信息"
}\0
```

- Login
登陆
```js
Login\n
{
    username: "naeioi",
    password: "ToOMoOYoO"
}\0
```

- LoginRes
登陆结果
```js
LoginRes\n
{
    /* code 
     * 0 成功
     * 1 用户名/密码错误
     */
    code: 0,
    session: "9e107d9d372bb6826bd81d3542a419d6",
    message: "额外信息"
}\0
```
- Tunnel
在Sender和Receiver之间建立新通道
```js
Tunnel\n
{
    /* role
     * - Tunnel指令发送端角色
     * 0 Sender
     * 1 Receiver
     */
    role: 0,
    /* mode
     * - 同步模式
     * 0 初始同步
     * 1 增量同步
     */
    mode: 0,
}\0
```

## Sender->Receiver
- DirInfo
```js
DirInfo\n
[
    {
        "filename": "v.mp4",
        "path": "/video",
        "md5": "9e107d9d372bb6826bd81d3542a419d6",
        "len": 1024,
        "modtime": "2011-10-08T07:07:09Z"
    },
    { ... }
]\0
```

- Push
```js
Push\n
[
    {
        "filename": "v.mp4",
        "path": "/video",
        "len": 1024,
        "offset": 0
    },
    { ... }
]\0
[Binary Data1]
[Binary Data2]
```

## Receiver->Sender
- Pull
```js
Pull\n
[
    {
        "filename": "v.mp4",
        "path": "/video",
        "len": 1024,
        "offset": 0
    },
    { ... }
]\0
```