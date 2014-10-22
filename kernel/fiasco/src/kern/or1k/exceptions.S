.text
.global kern_kdebug_entry
kern_kdebug_entry:
  l.sys 0x0404

.global vcpu_resume
vcpu_resume:
  l.sys 0x0404
