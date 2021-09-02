# teachingMaterial
MFCApplication Teaching material management system 高校教材管理系统asc
## 包含需求分析 用例图子系统顺序图等
# 高校教材管理系统
1.	引言
（1）	编写目的
               在当今这个数字化的时代，运用本系统将使学校工作效率比起以往不依赖
           电脑网络将会得到大幅度的提升，使各部门工作更具效率。
（2）	项目背景
               在规定的任务下通过小组的共同合作完成任务并根据自身实力适当增添内
           容。
（3）	定义
           一款便捷实用的高校教材管理系统。
（4）	参考资料
           《数据库系统概论》 《软件工程概论》
2.	需求概述
            
（1）	需求陈述（功能描述）
2.2.1登录注册

用户在登陆界面输入账号、密码，系统在用户信息中核对账号是否存，如果账号不存在，系统提示账号不存在请重新输入；否则，系统确定账号等级权限，并核对密码，如果密码正确，系统进入该帐号的用户界面，否则提示密码错误请重新输入。

新用户在注册界面选择教师用户或学院人员，并输入账户名称、密码，系统根据新用户的选择在对应的用户信息中添加新用户的信息，提示注册成功，系统转到登录界面。

2.2.2学校教材科

教材科人员：对教材、教师进行查询、增加、删除以及对信息的修改，对教师及学院用户的账户状态进行修改，管理出版社的信息，发布面向教师用户的公告，审核学院提交的征订申请。

查询教师（教材）：用户输入要查询的教师（教材）名称，系统在教师（教材）信息中进行核对，如果名称存在，系统输出对应教师（教材）的信息；否则，系统提示该教师（教材）不存在。

增加教师（教材）：用户输入要添加的账户名称和密码（教材名称），系统在教师（教材）信息中进行核对，如果名称存在，系统提示该用户已存在；否则，系统将新用户添加到教师（教材）信息中，并提示添加成功。

删除教师（教材）：用户输入要删除的账户（教材）名称，系统在教师（教材）信息中进行核对，如果名称不存在，系统提示该用户不存在或已被删除；否则，系统从教师（教材）信息中删除该用户信息，并提示删除成功。

修改教师（教材）信息：用户输入新的教师（教材）信息，系统将新的信息更新到教师（教材）信息中，并提示修改成功。

出版社信息的管理：
增加：用户输入出版社名称，系统在出版社信息中进行核对，如果该名称存在，系统提示该出版社已存在；否则，系统提示用户输入出版社的详细信息，并将新的出版社信息添加到出版社信息中，系统提示添加成功。
删除：用户输入出版社名称，系统在出版社信息中进行核对，如果该名称不存在（存在未完成的订单），系统提示该出版社不存在或已被删除（存在未完成的订单）；否则，系统从出版社信息中删除该出版社的信息，并提示删除成功。
修改：用户输入新的出版社信息，系统将新的信息更新到出版社信息中，并提示修改成功。

征订信息审核：教材科用户对征订进行审核，如果教材科人员选择不批准，系统将征订申请状态改为未通过，并提示学院用户及相应教师申请未通过；否则，系统将征订申请状态改为通过，生成订单。

系统公告：教材科用户在公告面板输入公告信息，系统将输入的信息显示到各个公告界面。

2.2.3教师用户

     教师用户：修改自己的信息、查询教材库现有教材、对没有的教材进行征订

     修改信息：教师用户在编辑信息界面输入修改的信息（密码、账户名称、联系方式等），系统将新的信息更新到教师信息中，并提示修改成功。

     查询功能：教师用户在查询界面输入要寻找的教材名称，系统在教材信息中进行核对，如果该教材不存在，系统提示教材不存在，并询问是否申请征订；否则，系统输出该教材的信息。

          征订功能：教师用户在征订界面输入要征订书的名称，形成订单，系统在教材信
          息中查询订单中的教材是否存在于教材库，如果存在，系统提示该教材存在，并
          向学院提交订单上全部书目的申请；否则，对教材库没有的教材进行添加，通过
          添加将需要的教材加入教材库，然后完善自己的订单。

2.2.4出版社

     出版社：接受来自学校的教材征订信息、修改出版社信息

修改出版社信息：用户输入新的出版社信息，系统将新的信息更新到出版社信息中，并提示修改成功。

         2.2.5学院审核人员

学院审核人员：对教材、教师进行查询、增加、删除以及对信息的修改，对教师用户的账户状态进行修改，审核教师提交的征订申请。

查询教师（教材）：用户输入要查询的教师（教材）名称，系统在教师（教材）信息中进行核对，如果名称存在，系统输出对应教师（教材）的信息；否则，系统提示该教师（教材）不存在。

增加教师（教材）：用户输入要添加的账户名称和密码（教材名称），系统在教师（教材）信息中进行核对，如果名称存在，系统提示该用户已存在；否则，系统将新用户添加到教师（教材）信息中，并提示添加成功。

删除教师（教材）：用户输入要删除的账户（教材）名称，系统在教师（教材）信息中进行核对，如果名称不存在，系统提示该用户不存在或已被删除；否则，系统从教师（教材）信息中删除该用户信息，并提示删除成功。

修改教师（教材）信息：用户输入新的教师（教材）信息，系统将新的信息更新到教师（教材）信息中，并提示修改成功。

征订信息审核：学院用户对征订申请进行审核，如果学院人员选择不批准，系统将征订申请状态改为未通过，并提示教师用户；否则，系统将征订申请状态改为通过并发送到学校教材科进行二次审核。

征订功能：学院用户在征订界面输入要征订书的名称，系统在教材信息中查询该教材是否存在，如果存在并且有剩余，系统提示该教材存在；否则，系统列出该书的版本及出版社供用户选择，用户选择教材版本并填写征订的详细信息，系统将交征订申请标明未审核状态并提到该教师用户对应的学院人员。


（2）	运行环境
       Windows 系统
3.	信息描述（数据模型）
 


4.	功能描述（功能模型）
 


5.	行为描述（行为模型）


 

